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

void setup() {
  Serial.begin(9600);
  AudioLogger::instance().begin(Serial, AudioLogger::Warning);

  // setup output
  auto cfg = kit.defaultConfig(TX_MODE);
  kit.begin(cfg);

 // setup additional buttons 
  kit.addDefaultActions();
  kit.addAction(kit.getKey(1), startStop);
  kit.addAction(kit.getKey(4), volumeUp);
  kit.addAction(kit.getKey(3), volumeDown);


  // setup player
  player.setVolume(0.7);
  player.setSilenceOnInactive(true);
  player.begin();
  player.setActive(false);
}


void loop() {
  player.copy();
  kit.processActions();
  if (Serial.available() > 0) {
    String song = Serial.readString();
    if(song.endsWith(".mp3")) {
      Serial.print("Received song: ");
      Serial.println(song);
      player.setPath(song.c_str());
    }
  }
}
