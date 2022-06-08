#include "mbedtls/aes.h"
#include "heltec.h"

#define BAND    433E6

char *key = "abcdefghijklmnop";

char *plainText = "placeholder text";


void encrypt(char * plainText, char * key, unsigned char * outputBuffer) {

  mbedtls_aes_context aes;

  mbedtls_aes_init( &aes );
  mbedtls_aes_setkey_enc( &aes, (const unsigned char*) key, strlen(key) * 8 );
  mbedtls_aes_crypt_ecb( &aes, MBEDTLS_AES_ENCRYPT, (const unsigned char*)plainText, outputBuffer);
  mbedtls_aes_free( &aes );
}

void decrypt(unsigned char * chipherText, char * key, unsigned char * outputBuffer) {

  mbedtls_aes_context aes;

  mbedtls_aes_init( &aes );
  mbedtls_aes_setkey_dec( &aes, (const unsigned char*) key, strlen(key) * 8 );
  mbedtls_aes_crypt_ecb(&aes, MBEDTLS_AES_DECRYPT, (const unsigned char*)chipherText, outputBuffer);
  mbedtls_aes_free( &aes );
}

void setup() {
  Heltec.begin(true /*DisplayEnable Enable*/, true /*Heltec.LoRa Disable*/, true /*Serial Enable*/, true /*PABOOST Enable*/, BAND /*long BAND*/);
  Serial.begin(115200);

}

//for AES GCM mode (check if encryption is correct or not)
char *keyc = "abcdefghijklmnop";

void loop() {

  if (strcmp(key, keyc) == 0)
  {
    int packetSize = LoRa.parsePacket();
    if (packetSize) {
      // received a packet

      // read packet
      String message = "";

      while (LoRa.available())
      {
        message += (char)LoRa.read();
      }

      char *plainText = (char *)message.c_str();


      unsigned char cipherTextOutput[16];
      unsigned char decipheredTextOutput[16];

      encrypt(plainText, key, cipherTextOutput);


      Serial.println("\nOriginal plain text:");
      Serial.println(plainText);




      Serial.println("\nCiphered text:");
      for (int i = 0; i < 16; i++) {

        char str[3];

        sprintf(str, "%02x", (int)cipherTextOutput[i]);
        Serial.print(str);
      }

      decrypt(cipherTextOutput, key, decipheredTextOutput);
      Serial.println("\n\nDeciphered text:");
      for (int i = 0; i < 16; i++) {
        Serial.print((char)decipheredTextOutput[i]);
      }
      Serial.println("");
      Serial.println("");
      //lora 32 display
      Heltec.display->clear();
      Heltec.display->setTextAlignment(TEXT_ALIGN_LEFT);
      Heltec.display->setFont(ArialMT_Plain_10);
      Heltec.display->drawString(5, 5, String(plainText));
      Heltec.display->display();

    }
    delay(3000);
  }
  else {
    Serial.println("wrong encryption key");
    delay(3000);
  }
}
