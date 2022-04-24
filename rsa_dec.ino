#include "mbedtls/pk.h"

void setup() {
  int ret = 0;
mbedtls_pk_context pk;

mbedtls_pk_init( &pk );

/*
 * Read the RSA privatekey
 */
if( ( ret = mbedtls_pk_parse_keyfile( &pk, "our-key.pem", "" ) ) != 0 )
{
    printf( " failed\n  ! mbedtls_pk_parse_keyfile returned -0x%04x\n", -ret );
    goto exit;
}

}

void loop() {
  unsigned char result[MBEDTLS_MPI_MAX_SIZE];
size_t olen = 0;

/*
 * Calculate the RSA encryption of the data.
 */
printf( "\n  . Generating the encrypted value" );
fflush( stdout );

if( ( ret = mbedtls_pk_decrypt( &pk, to_decrypt, to_decrypt_len, result, &olen, sizeof(result),
                                mbedtls_ctr_drbg_random, &ctr_drbg ) ) != 0 )
{
    printf( " failed\n  ! mbedtls_pk_decrypt returned -0x%04x\n", -ret );
    goto exit;
}


}
