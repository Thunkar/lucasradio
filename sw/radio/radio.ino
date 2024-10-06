#include "AudioTools.h" // https://github.com/pschatzmann/arduino-audio-tools
#include "AudioLibs/AudioBoardStream.h" // https://github.com/pschatzmann/arduino-audio-driver
#include "AudioLibs/AudioSourceSDFAT.h"
#include "AudioCodecs/CodecMP3Helix.h" // https://github.com/pschatzmann/arduino-libhelix
#include "Arduino.h"
#include "esp_task_wdt.h"
#include <PN532_I2C_CUSTOM.h>
#include <PN532.h> // https://github.com/elechouse/PN532
#include <NfcAdapter.h> // https://github.com/don/NDEF
#include "AudioKitEs8388v1Custom.h"

// We are not using aux in, so we don't care about jack detection and can reuse the pin
#define LID_PIN 12

#define DEBUG

#ifdef DEBUG
#define NDEF_USE_SERIAL 0
#endif

// Use I2C Bus 1 to avoid audio conflicts
TwoWire customI2C = TwoWire(1);
// We have to reuse UART RX pin and LED pin because we run out of IO
PN532_I2C_CUSTOM pn532i2c(customI2C, 22, 3);
NfcAdapter nfc = NfcAdapter(pn532i2c);

const char* startFilePath = "empty";
const char* ext = "mp3";
SdSpiConfig sdcfg(PIN_AUDIO_KIT_SD_CARD_CS, DEDICATED_SPI, SD_SCK_MHZ(10), &SPI);
AudioSourceSDFAT source(startFilePath, ext, sdcfg);
PinsAudioKitEs8388v1CustomClass PinsAudioKitEs8388v1Custom;
AudioBoard AudioKitEs8388v1Custom(AudioDriverES8388, PinsAudioKitEs8388v1Custom);
AudioBoardStream kit(AudioKitEs8388v1Custom);
MP3DecoderHelix decoder;
AudioPlayer player(source, kit, decoder);
String currentFolder;
volatile bool isOpen = false;
volatile long lastRead = 0;
// Limit reading NFC to once every second for performance reasons
long readInterval = 1000;
bool firstTimeSetFolder = true;

void volumeUp(bool, int, void*) {
  float nextVolume = constrain(player.volume() + 0.1, 0.0, 1.0);
  player.setVolume(nextVolume);
  #ifdef DEBUG
  Serial.print("Volume up: ");
  Serial.println(nextVolume);
  #endif
}

void volumeDown(bool, int, void*) {
  float nextVolume = constrain(player.volume() - 0.1, 0.0, 1.0);
  player.setVolume(nextVolume);
  #ifdef DEBUG
  Serial.print("Volume down: ");
  Serial.println(nextVolume);
  #endif
}

void startStop(bool, int, void*) {
  bool nextState = !player.isActive() && !isOpen;
  player.setActive(nextState);
  #ifdef DEBUG
  Serial.print("Play: ");
  Serial.println(nextState);
  #endif
}

void previous(bool, int, void*) {
  source.setPath(currentFolder.c_str());
  player.previous();
  #ifdef DEBUG
  Serial.println("Previous");
  #endif
}

void next(bool, int, void*) {
  source.setPath(currentFolder.c_str());
  player.next();
  #ifdef DEBUG
  Serial.println("Next");
  #endif
}

String readNFCTag() {
  String payloadAsString = "empty";

  if (nfc.tagPresent()) {
    NfcTag tag = nfc.read();
    NdefMessage message = tag.getNdefMessage();
    NdefRecord record = message.getRecord(0);
    int payloadLength = record.getPayloadLength();
    byte payload[payloadLength];
    record.getPayload(payload);
    payloadAsString = "";
    for (int c = 3; c < payloadLength; c++) {
      payloadAsString += (char)payload[c];
    }
  }
  return payloadAsString;
}

void updateCurrentFolder() {
    String command = readNFCTag();
    if (command.startsWith("P->")) {
      command.trim();
      String receivedFolder = command.substring(3);
      if (receivedFolder.equals(currentFolder)) {
        return;
      }
      currentFolder = receivedFolder;
      if (!firstTimeSetFolder) {
        firstTimeSetFolder = false;
        player.end();
      }
      #ifdef DEBUG
      Serial.print("Received command: ");
      Serial.println(command);
      Serial.print("Selecting folder: ");
      Serial.println(currentFolder);
      #endif
      source.setPath(currentFolder.c_str());
      player.setSilenceOnInactive(true);
      player.begin(0, false);
    }
}

void setup() {
  // Setup hall effect sensor
  pinMode(LID_PIN, INPUT_PULLUP);
  isOpen = digitalRead(LID_PIN);

  #ifdef DEBUG
  // Setup serial
  Serial.begin(9600);
  Serial.setTimeout(10);
  // Setup logging
  AudioLogger::instance().begin(Serial, AudioLogger::Warning);
  #endif

  // Setup output
  auto cfg = kit.defaultConfig(TX_MODE);
  kit.begin(cfg);

  // Setup additional buttons
  kit.addDefaultActions();
  kit.addAction(kit.getKey(1), startStop);
  kit.addAction(kit.getKey(3), previous);
  kit.addAction(kit.getKey(4), next);
  kit.addAction(kit.getKey(5), volumeDown);
  kit.addAction(kit.getKey(6), volumeUp);

  // Setup player
  player.setVolume(0.7);
  // Setup nfc
  nfc.begin();
  updateCurrentFolder();
}


void loop() {
  player.copy();
  kit.processActions();
  bool wasOpen = isOpen;
  isOpen = digitalRead(LID_PIN);
  if (isOpen != wasOpen) {
    if (isOpen) {
      player.end();
      currentFolder = "empty";
      source.setPath(currentFolder.c_str());
      player.setSilenceOnInactive(true);
      player.begin(0, false);
    }
    #ifdef DEBUG
    Serial.println(isOpen);
    #endif
  }
  long now = millis();
  if (wasOpen && !isOpen && !player.isActive() && (now - lastRead) > readInterval) {
    lastRead = now;
    updateCurrentFolder();
  }
}
