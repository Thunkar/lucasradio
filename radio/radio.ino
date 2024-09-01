/**
 * @file player-sd-audiokit.ino
 * @brief see https://github.com/pschatzmann/arduino-audio-tools/blob/main/examples/examples-audiokit/player-sdfat-audiokit/README.md
 * Make sure that the pins are set to off, on, on, off, off
 * @author Phil Schatzmann
 * @copyright GPLv3
 */


#include "AudioTools.h"
#include "AudioLibs/AudioBoardStream.h"
#include "AudioLibs/AudioSourceSDFAT.h" // or AudioSourceIdxSDFAT.h
#include "AudioCodecs/CodecMP3Helix.h"

const char *startFilePath="/";
const char* ext="mp3";
SdSpiConfig sdcfg(PIN_AUDIO_KIT_SD_CARD_CS, DEDICATED_SPI, SD_SCK_MHZ(10) , &SPI);
AudioSourceSDFAT source(startFilePath, ext, sdcfg);
AudioBoardStream kit(AudioKitEs8388V1);
MP3DecoderHelix decoder;  // or change to MP3DecoderMAD
AudioPlayer player(source, kit, decoder);
String currentFolder;

void volumeUp(bool, int, void*) {
  float currentVolume = player.volume();
  player.setVolume(constrain(currentVolume + 0.1, 0.0, 1.0));
}

void volumeDown(bool, int, void*) {
  float currentVolume = player.volume();
  player.setVolume(constrain(currentVolume - 0.1, 0.0, 1.0));
}

void startStop(bool, int, void*) {
   player.setActive(!player.isActive());
}

void previous(bool, int, void*) {
  source.setPath(currentFolder.c_str());
  player.previous();
}

void next(bool, int, void*) {
  source.setPath(currentFolder.c_str());
  player.next();
}

void setup() {
  Serial.begin(9600);
  Serial.setTimeout(10);
  AudioLogger::instance().begin(Serial, AudioLogger::Warning);

  // setup output
  auto cfg = kit.defaultConfig(TX_MODE);
  kit.begin(cfg);

 // setup additional buttons 
  kit.addDefaultActions();
  kit.addAction(kit.getKey(1), startStop);
  kit.addAction(kit.getKey(3), previous);
  kit.addAction(kit.getKey(4), next);
  kit.addAction(kit.getKey(5), volumeDown);
  kit.addAction(kit.getKey(6), volumeUp);


  // setup player
  player.setVolume(0.7);
  player.setSilenceOnInactive(true);
  player.begin(0, false);
}


void loop() {
  player.copy();
  kit.processActions();
  if (Serial.available() > 0) {
    String command = Serial.readString();
    if(command.startsWith("P->") && command.endsWith("\n")) {
      player.end();
      command.trim();
      Serial.print("Received command: ");
      Serial.println(command);
      currentFolder = command.substring(3);
      Serial.print("Selecting folder: ");
      Serial.println(currentFolder);
      source.setPath(currentFolder.c_str());
      player.begin(0, false);
    }
  }
}
