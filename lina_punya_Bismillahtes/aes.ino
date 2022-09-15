#include "mbedtls/aes.h"
void encrypt(char * (plainText), char * key, unsigned char * outputBuffer){
  
  mbedtls_aes_context aes;

  mbedtls_aes_init( &aes );
  mbedtls_aes_setkey_enc( &aes, (const unsigned char*) key, strlen(key) * 8 );
  mbedtls_aes_crypt_ecb( &aes, MBEDTLS_AES_ENCRYPT, (const unsigned char*)plainText, outputBuffer);
  mbedtls_aes_free( &aes );
}

void decrypt(unsigned char * chipherText, char * key, unsigned char * outputBuffer){

  mbedtls_aes_context aes;

  mbedtls_aes_init( &aes );
  mbedtls_aes_setkey_dec( &aes, (const unsigned char*) key, strlen(key) * 8 );
  mbedtls_aes_crypt_ecb(&aes, MBEDTLS_AES_DECRYPT, (const unsigned char*)chipherText, outputBuffer);
  mbedtls_aes_free( &aes );
}

void rnd(void){
  char *key = "abcdefghijklmnopqrstuvwxyz0123456789";
  int randomValue = random(0,37);
  String krand = "";
  for(int i = 0; i<16; i++){
    String krand = krand + key[randomValue];
    Serial.print(krand);
  }
  Serial.println();
}
