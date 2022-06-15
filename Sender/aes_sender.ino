#include "Cipher.h"
#include "mbedtls/aes.h"
#include "heltec.h"

Cipher * cipher = new Cipher();
#define BAND    433E6

String data = "placeholder text";

void setup() {
  Heltec.begin(true /*DisplayEnable Enable*/, true /*Heltec.LoRa Disable*/, true /*Serial Enable*/, true /*PABOOST Enable*/, BAND /*long BAND*/);
  Serial.begin(115200);
}

void loop()
{
  char * key = "abcdefghijklmnop";
  cipher->setKey(key);
  Serial.print('\n');

  if (Serial.available() > 0) {
    // read the incoming string:
    data = Serial.readString();
  }
  Serial.println(data);
  String cipherString = cipher->encryptString(data);
  Serial.print('\n');
  Serial.println(cipherString);
  Serial.print('\n');
  LoRa.beginPacket();
  LoRa.setTxPower(14, RF_PACONFIG_PASELECT_PABOOST);
  LoRa.println(cipherString);
  LoRa.endPacket();
  delay(5000);

  //lora 32 display
  Heltec.display->clear();
  Heltec.display->setTextAlignment(TEXT_ALIGN_LEFT);
  Heltec.display->setFont(ArialMT_Plain_16);
  Heltec.display->drawString(5, 5, String(data));
  Heltec.display->display();
}
