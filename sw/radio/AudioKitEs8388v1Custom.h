#include "Driver.h"
#include "DriverPins.h"
#include "AudioBoard.h"

class PinsAudioKitEs8388v1CustomClass : public DriverPins {
 public:
  PinsAudioKitEs8388v1CustomClass() {
    // sd pins
    addSPI(ESP32PinsSD);
    // add i2c codec pins: scl, sda, port, frequency
    addI2C(PinFunction::CODEC, 32, 33);
    // add i2s pins: mclk, bck, ws,data_out, data_in ,(port)
    addI2S(PinFunction::CODEC, 0, 27, 25, 26, 35);

    // add other pins
    addPin(PinFunction::KEY, 36, PinLogic::InputActiveLow, 1);
    //addPin(PinFunction::KEY, 13, PinLogic::InputActiveLow, 2); // Used by SD card SPI
    addPin(PinFunction::KEY, 19, PinLogic::InputActiveLow, 3);
    addPin(PinFunction::KEY, 23, PinLogic::InputActiveLow, 4);
    addPin(PinFunction::KEY, 18, PinLogic::InputActiveLow, 5);
    addPin(PinFunction::KEY, 5, PinLogic::InputActiveLow, 6);
    //addPin(PinFunction::AUXIN_DETECT, 12, PinLogic::InputActiveLow); // We don't need aux in detection, but lid detection
    addPin(PinFunction::HEADPHONE_DETECT, 39, PinLogic::InputActiveLow);
    addPin(PinFunction::PA, 21, PinLogic::Output);
    //addPin(PinFunction::LED, 22, PinLogic::Output); // We need this for the I2C
  }
};