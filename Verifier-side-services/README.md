# Verifier-side-services

This repository includes the C code of a library featuring different functions related to the research presented in the following paper:

**Title:** [Kyber AHE: An Easy-to-Implement Additive Homomorphic Encryption Scheme Based on Kyber and Its Application in Biometric Template Protection](https://doi.org)  
**DOI:** https://doi.org/10.3390/math13182914

### Implementation

The library implements the following functions, distributed across the system entities as described in the paper:

1. `indcpa_keypair` (Implementation of **Kyber.AHE.KeyGen**): Executed by the **Authentication Server (AS)** to generate the public-private key pair.
2. `indcpa_enc` (Implementation of **Kyber.AHE.Encrypt**): Executed by the **Client** (an **embedded IoT device**) to secure data at the source.
4. `indcpa_eval` (Implementation of **Kyber.AHE.Eval**): Executed by the **Database Server (DBS)** to perform the modulo 2 addition of two 256-bit bitstrings directly in the encrypted domain.
5. `indcpa_dec` (Implementation of **Kyber.AHE.Decrypt**): Executed by the **Authentication Server (AS)** to decrypt the resulting modulo 2 addition obtained from the evaluation process.

In order to use it, please include the `indcpa.h` file.
