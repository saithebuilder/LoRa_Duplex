#include "mbedtls/aes.h"
#include "heltec.h"
#define BAND    433E6 //setting the LoRa bands to 433 mhz
mbedtls_aes_context aes;

unsigned char key[32] = 1234567891234567; // 128 bit - AES = 16 bytes for key
unsigned char iv[16];

unsigned char output[128];
unsigned char input[128];

size_t input_len = 40;
size_t output_len = 0;

void setup() {
  Heltec.begin(true /*DisplayEnable Enable*/, true /*Heltec.Heltec.Heltec.LoRa Disable*/, true /*Serial Enable*/, true /*PABOOST Enable*/, BAND /*long BAND*/);
  //setup code to enable LoRa

  Heltec.display->init();  //display settings
  Heltec.display->flipScreenVertically();
  Heltec.display->setFont(ArialMT_Plain_10);
  Heltec.display->clear();

  Heltec.display->drawString(0, 0, "Heltec.LoRa Initial success!");
  Heltec.display->display(); //display check
  delay(2000);

  LoRa.receive();
  unsigned char input[128]  = LoRa.parsePacket(); // recieve encrypted data via LoRa

  mbedtls_aes_setkey_enc( &aes, key, 256 );
  mbedtls_aes_crypt_cbc( &aes, MBEDTLS_AES_ENCRYPT, 48, iv, input, output ); // AES function from mbedtls library, same function is
  // used to decrypt as well
}

void loop() {
  Heltec.display->clear();
  Heltec.display->setTextAlignment(TEXT_ALIGN_LEFT);
  Heltec.display->setFont(ArialMT_Plain_10);
  Heltec.display->drawString(0, 0, String("AES Plain Text"));
  Heltec.display->drawString(0, 15, String((char*)output)); // convert unsigned char to String to display the output text
  Heltec.display->display();
}
