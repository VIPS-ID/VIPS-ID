#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>

#include "indcpa.h"
#include "kem.h"
#include "params.h"
#include "randombytes.h"
#include "reduce.h"

void XOR(uint8_t m1[KYBER_INDCPA_MSGBYTES], uint8_t m2[KYBER_INDCPA_MSGBYTES], uint8_t m3[KYBER_INDCPA_MSGBYTES]) {
    for(int i=0; i<KYBER_INDCPA_MSGBYTES; i++) {
        m3[i] = m1[i] ^ m2[i];
    }
}

int COMP(uint8_t m1[KYBER_INDCPA_MSGBYTES], uint8_t m2[KYBER_INDCPA_MSGBYTES]) {
    int f=0;

    for(int i=0; i<KYBER_INDCPA_MSGBYTES; i++) {
        if(m1[i] != m2[i])
            f++;
    }

    return f;
}

int main(void) {
    uint8_t pk[KYBER_INDCPA_PUBLICKEYBYTES];
    uint8_t sk[KYBER_INDCPA_SECRETKEYBYTES];
    uint8_t c1[KYBER_INDCPA_BYTES];
    uint8_t c2[KYBER_INDCPA_BYTES];
    uint8_t cDiff[KYBER_INDCPA_BYTES];
    uint8_t coins1[KYBER_SYMBYTES];
    uint8_t coins2[KYBER_SYMBYTES];
    uint8_t m1[KYBER_INDCPA_MSGBYTES];
    uint8_t m2[KYBER_INDCPA_MSGBYTES];
    uint8_t mDiff[KYBER_INDCPA_MSGBYTES];
    uint8_t mTest[KYBER_INDCPA_MSGBYTES];
    uint32_t cnt = 0;


    // Genero mensaje 1
    randombytes(m1, KYBER_INDCPA_MSGBYTES);

    // Genero mensaje 2
    randombytes(m2, KYBER_INDCPA_MSGBYTES);

    // Generación de claves privada y pública
    indcpa_keypair(pk, sk);

    // encryption of msg 1
    randombytes(coins1, KYBER_SYMBYTES);
    indcpa_enc( c1, m1, pk, coins1);

    // encryption of msg 1
    randombytes(coins2, KYBER_SYMBYTES); 
    indcpa_enc( c2, m2, pk, coins2);

    // addition modulo 2 in the encrypted domain
    indcpa_eval(c1, c2, cDiff);

    // decrypt the comparison
    indcpa_dec(mDiff, cDiff, sk);

    XOR(m1, m2, mTest);

    if(COMP(mDiff, mTest))
        cnt++;

    printf("\nmsg1 XOR msg2:\n");
    for(int i=0; i<KYBER_INDCPA_MSGBYTES; i++) {
        printf("%02x", mTest[i]);
    }

    printf("\nResult of the decryption:\n");
    for(int i=0; i<KYBER_INDCPA_MSGBYTES; i++) {
        printf("%02x", mDiff[i]);
    }

    return 0;
}