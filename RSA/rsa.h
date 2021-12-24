#ifndef RSA_H
#define RSA_H

#include <stdint.h>

uint64_t exp_mod(uint64_t n, uint64_t power, uint64_t mod);

int64_t inv_mod(int64_t a, int64_t p);

void I2OSP(uint64_t n, uint8_t len, uint8_t *OS);

uint64_t OS2IP(uint8_t *OS, uint8_t len);

uint64_t rsa_encrypt(uint64_t clear_text, uint64_t pub_exp, uint64_t module );

uint64_t rsa_decrypt(uint64_t cipher_text, uint64_t private_exp, uint64_t module );

#endif /*RSA_H*/