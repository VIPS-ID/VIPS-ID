# A prover-side software for things identification

This repository contains the software components for the prover side, focusing on device identification and characterization.

## BPUF Characterization

This module is dedicated to the characterization of a **BPUF (Behavioral Physical Unclonable Function)** and includes the following components:

*   **`physical_response_analysis.m`**: The main MATLAB script used to analyze the physical response of the BPUF. This script utilizes the following auxiliary functions:
    *   `lee_medidas`: For reading the measurement data.
    *   `reshape_to_resp_PUF`: For formatting the data into the PUF response structure.
    *   `distanciaHamming`: For calculating the Hamming distance between responses.
    *   `distanciaHamming_average`: For computing the average Hamming distance across multiple samples.
*   **`behavioral_response_analysis.m`**: The main MATLAB script used to analyze the behavioral responses of the BPUF. This script utilizes the following auxiliary functions:
    *   `lee_medidas_BUF`: For computing the behavioral response from a set of physical responses.
    *   `reshape_to_resp_PUF`: For formatting the data into the PUF response structure.
    *   `distanciaJaccard_mod`: For calculating the modified Jaccard distance.
    *   `distanciaJaccard_mod_average`: For computing the average modified Jaccard distance across multiple samples.

## PUF Response Extraction (Baseline)

*   **`puf_extraction_base_code/`**: This directory contains the base code for extracting responses from the PUF. Note that this is provided as a **sample/reference implementation** and was not the version used for the final data collection in this project.
