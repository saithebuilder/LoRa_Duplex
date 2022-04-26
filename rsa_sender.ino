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
  if ( ( ret = mbedtls_pk_parse_public_keyfile( &pk, "our-key.pub" ) ) != 0 ) //pem file where our private and public keys are stored
  {
    printf( " failed\n  ! mbedtls_pk_parse_public_keyfile returned -0x%04x\n", -ret );
    goto exit;
  }

}

void loop() {

  unsigned char buf[MBEDTLS_MPI_MAX_SIZE];
  size_t olen = 0;

  printf( "\n  . Generating the encrypted value" );
  fflush( stdout );

  unsigned char to_encrypt = "RSA Plain Text"; // text we are encrypting

  if ( ( ret = mbedtls_pk_encrypt( &pk, to_encrypt, to_encrypt_len,
                                   buf, &olen, sizeof(buf),
                                   mbedtls_ctr_drbg_random, &ctr_drbg ) ) != 0 ) //encrypting the plain text
  {
    printf( " failed\n  ! mbedtls_pk_encrypt returned -0x%04x\n", -ret );
    goto exit;
  }
  Heltec.display->clear();
  Heltec.display->setTextAlignment(TEXT_ALIGN_LEFT);
  Heltec.display->setFont(ArialMT_Plain_10);
  Heltec.display->drawString(0, 0, String("RSA Cipher Text"));
  Heltec.display->display();

  LoRa.beginPacket(); //sending encrypted text via LoRa
  LoRa.setTxPower(14, RF_PACONFIG_PASELECT_PABOOST);
  LoRa.print(String((int*)ret));
  LoRa.endPacket();
}
