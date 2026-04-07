#ifndef INDCPA_H
#define INDCPA_H

#include <stdint.h>
#include "params.h"
#include "polyvec.h"

static void pack_ciphertext(uint8_t r[KYBER_INDCPA_BYTES], polyvec *b, poly *v);
static void unpack_ciphertext(polyvec *b, poly *v, const uint8_t c[KYBER_INDCPA_BYTES]);

#define gen_matrix KYBER_NAMESPACE(gen_matrix)
void gen_matrix(polyvec *a, const uint8_t seed[KYBER_SYMBYTES], int transposed);
#define indcpa_keypair KYBER_NAMESPACE(indcpa_keypair)
void indcpa_keypair(uint8_t pk[KYBER_INDCPA_PUBLICKEYBYTES],
                    uint8_t sk[KYBER_INDCPA_SECRETKEYBYTES]);


#define indcpa_dec KYBER_NAMESPACE(indcpa_dec)
void indcpa_dec(uint8_t m[KYBER_INDCPA_MSGBYTES],
                const uint8_t c[KYBER_INDCPA_BYTES],
                const uint8_t sk[KYBER_INDCPA_SECRETKEYBYTES]);

#define indcpa_eval KYBER_NAMESPACE(indcpa_eval)
void indcpa_eval(uint8_t c1[KYBER_INDCPA_BYTES], uint8_t c2[KYBER_INDCPA_BYTES], uint8_t cDiff[KYBER_INDCPA_BYTES]);
#define indcpa_eval_sub KYBER_NAMESPACE(indcpa_eval_sub)
void indcpa_eval_sub(uint8_t c1[KYBER_INDCPA_BYTES], uint8_t c2[KYBER_INDCPA_BYTES], uint8_t cDiff[KYBER_INDCPA_BYTES]);


#endif
