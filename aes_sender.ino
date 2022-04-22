#include "mbedtls/aes.h"
#include "heltec.h"
#define BAND    433E6
mbedtls_aes_context aes;

unsigned char key[32] = "key";
unsigned char iv[16];

unsigned char input [128] = "plain text example to send over LoRa";
unsigned char output[128];

size_t input_len = 40;
size_t output_len = 0;

void setup() {
  Heltec.begin(true /*DisplayEnable Enable*/, true /*Heltec.Heltec.Heltec.LoRa Disable*/, true /*Serial Enable*/, true /*PABOOST Enable*/, BAND /*long BAND*/);

  Heltec.display->init();
  Heltec.display->flipScreenVertically();
  Heltec.display->setFont(ArialMT_Plain_10);
  delay(1500);
  Heltec.display->clear();

  Heltec.display->drawString(0, 0, "Heltec.LoRa Initial success!");
  Heltec.display->display();
  delay(1000);

  mbedtls_aes_setkey_enc( &aes, key, 256 );
  mbedtls_aes_crypt_cbc( &aes, MBEDTLS_AES_ENCRYPT, 48, iv, input, output );
}

void loop() {
  Heltec.display->clear();
  Heltec.display->setTextAlignment(TEXT_ALIGN_LEFT);
  Heltec.display->setFont(ArialMT_Plain_10);
  Heltec.display->drawString(0, 0, String("CT="));
  Heltec.display->drawString(25, 0, String((char*)output));
  Heltec.display->display();

  LoRa.beginPacket();
  LoRa.setTxPower(14, RF_PACONFIG_PASELECT_PABOOST);
  LoRa.print(String((char*)output));
  LoRa.endPacket();
}
