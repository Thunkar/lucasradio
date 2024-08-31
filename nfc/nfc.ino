#include "Arduino.h"
#include <PN532_I2C.h>
#include <PN532.h>
#include <NfcAdapter.h>

#define NDEF_USE_SERIAL 0;

PN532_I2C pn532i2c(Wire);
NfcAdapter nfc = NfcAdapter(pn532i2c);

void setup(void) {
  Serial.begin(9600);
  while(!Serial) {
    ;
  }

  nfc.begin();
}

void loop(void) {
   if (nfc.tagPresent())
  {
    NfcTag tag = nfc.read();

    if (tag.hasNdefMessage())
    {

      NdefMessage message = tag.getNdefMessage();

      int recordCount = message.getRecordCount();
      for (int i = 0; i < recordCount; i++)
      {
        NdefRecord record = message.getRecord(i);
        int payloadLength = record.getPayloadLength();
        byte payload[payloadLength];
        record.getPayload(payload);

        String payloadAsString = "";
        for (int c = 3; c < payloadLength; c++) {
          payloadAsString += (char)payload[c];
        }

        if(payloadAsString.endsWith(".mp3")) {
          Serial.println(payloadAsString);
        }
      }
    }
  }
}