#include "mbedtls/pk.h"
#include "heltec.h"
#define BAND    433E6 //setting the LoRa bands to 433 mhz

void setup() {
  Heltec.begin(true /*DisplayEnable Enable*/, true /*Heltec.Heltec.Heltec.LoRa Disable*/, true /*Serial Enable*/, true /*PABOOST Enable*/, BAND /*long BAND*/);
  //setup code to enable LoRa

  Heltec.display->init(); //display settings
  Heltec.display->flipScreenVertically();
  Heltec.display->setFont(ArialMT_Plain_10);
  Heltec.display->clear();

  Heltec.display->drawString(0, 0, "Heltec.LoRa Initial success!");
  Heltec.display->display(); //display check
  delay(2000);

  int ret = 0;
  mbedtls_pk_context pk;
  mbedtls_pk_init( &pk );

  // Read the pem file
  if ( ( ret = mbedtls_pk_parse_keyfile( &pk, "our-key.pem", "" ) ) != 0 ) //pem file where our private and public keys are stored
  {
    printf( " failed\n  ! mbedtls_pk_parse_keyfile returned -0x%04x\n", -ret );
    goto exit;
  }
  Heltec.display->init(); //display settings
  Heltec.display->flipScreenVertically();
  Heltec.display->setFont(ArialMT_Plain_10);
  Heltec.display->clear();

  Heltec.display->drawString(0, 0, "Heltec.LoRa Initial success!");
  Heltec.display->display(); //display check
  delay(2000);
}

void loop() {
  LoRa.receive();
  unsigned char to_decrypt  = LoRa.parsePacket(); // recieve encrypted data via LoRa

  unsigned char result[MBEDTLS_MPI_MAX_SIZE];
  size_t olen = 0;


  printf( "\n  . Generating the encrypted value" );
  fflush( stdout );

  if ( ( ret = mbedtls_pk_decrypt( &pk, to_decrypt, to_decrypt_len, result, &olen, sizeof(result),
                                   mbedtls_ctr_drbg_random, &ctr_drbg ) ) != 0 ) //encrypting the cipher text
  {
    printf( " failed\n  ! mbedtls_pk_decrypt returned -0x%04x\n", -ret );
    goto exit;
  }

  Heltec.display->clear();
  Heltec.display->setTextAlignment(TEXT_ALIGN_LEFT);
  Heltec.display->setFont(ArialMT_Plain_10);
  Heltec.display->drawString(0, 0, String("RSA Plain Text"));
  Heltec.display->drawString(0, 15, String((int*)ret)); //convert int to String to display the output text
  Heltec.display->display();
}
