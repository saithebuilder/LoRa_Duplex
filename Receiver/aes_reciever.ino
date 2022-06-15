#include "Cipher.h"
#include "mbedtls/aes.h"
#include "heltec.h"

Cipher * cipher = new Cipher();
#define BAND    433E6

void setup() {
  Heltec.begin(true /*DisplayEnable Enable*/, true /*Heltec.LoRa Disable*/, true /*Serial Enable*/, true /*PABOOST Enable*/, BAND /*long BAND*/);
  Serial.begin(115200);
}

void loop()
{
  int packetSize = LoRa.parsePacket();
  if (packetSize)
  {
    while (LoRa.available())
    {
      char * key = "abcdefghijklmnop";
      cipher->setKey(key);
      String cipherString = LoRa.readString();
      Serial.print('\n');
      Serial.println(cipherString);
      String decipheredString = cipher->decryptString(cipherString);
      Serial.println(decipheredString);
      Serial.print('\n');
      
      //lora 32 display
      Heltec.display->clear();
      Heltec.display->setTextAlignment(TEXT_ALIGN_LEFT);
      Heltec.display->setFont(ArialMT_Plain_16);
      Heltec.display->drawString(5, 5, String(decipheredString));
      Heltec.display->display();
    }
  }
}
