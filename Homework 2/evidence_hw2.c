#include <stdlib.h>
#include <stdio.h>
#include "hw2.h"

/* evidence_tens_letters: test tens_letters */
void evidence_tens_letters() {
    printf("*** testing tens_letters\n");

    printf("- expecting 4: %hhu\n", tens_letters(0));
    printf("- expecting 3: %hhu\n", tens_letters(10));
    printf("- expecting 5: %hhu\n", tens_letters(20));
    printf("- expecting 5: %hhu\n", tens_letters(30));
    printf("- expecting 5: %hhu\n", tens_letters(40));
    printf("- expecting 4: %hhu\n", tens_letters(50));
    printf("- expecting 5: %hhu\n", tens_letters(60));
    printf("- expecting 6: %hhu\n", tens_letters(70));
    printf("- expecting 6: %hhu\n", tens_letters(80));
    printf("- expecting 5: %hhu\n", tens_letters(90));
    // tens_letters(255);
    // tens_letters(15);
    // tens_letters(100);
    // tens_letters(95);
}


/* evidence_common_divisors: test common_divisors */
void evidence_common_divisors() {
    printf("*** testing common_divisors\n");

    printf("- expecting 1 2 4 8: ");
    common_divisors(8, 16);

    printf("- expecting 1 2 4 8: ");
    common_divisors(24, 136);

    printf("- expecting 1 7: ");
    common_divisors(7, 49);

    printf("- expecting 1: ");
    common_divisors(12, 13);

    printf("- expecting 1 3 9 27: ");
    common_divisors(54, 243);

    printf("- expecting 1 2 3 4 6 8 12 24: ");
    common_divisors(72, 48);

    printf("- expecting 1 17: ");
    common_divisors(17, 17);
}


/* evidence_legal_keys: test legal_keys */
void evidence_legal_keys() {
    printf("*** testing legal_keys\n");

    printf("- expecting 81: %u\n", legal_keys(3, 2));
    printf("- expecting 16: %u\n", legal_keys(2, 1));
    printf("- expecting 2: %u\n", legal_keys(2, 0));
    printf("- expecting 5430: %u\n", legal_keys(10, 5));
    printf("- expecting 61771: %u\n", legal_keys(17, 11));
    printf("- expecting 0: %u\n", legal_keys(0, 5));
    printf("- expecting 3011: %u\n", legal_keys(9, 4));
}


/* evidence_periods_for_yield: test periods_for_yield */
void evidence_periods_for_yield() {
    printf("*** testing periods_for_yield\n");

    printf("- expecting 2: %u\n", periods_for_yield(0.1, 0.2));
    printf("- expecting 19: %u\n", periods_for_yield(0.05, 1.5));
    printf("- expecting 93: %u\n", periods_for_yield(0.01, 1.5));
    printf("- expecting 241: %u\n", periods_for_yield(0.01, 10));
    printf("- expecting 26: %u\n", periods_for_yield(0.1, 10));
    printf("- expecting 0: %u\n", periods_for_yield(0.05, 0));
    printf("- expecting 0: %u\n", periods_for_yield(0, 0));
    // periods_for_yield(0.5, -0.5);
    // periods_for_yield(0, 0.5);
    // periods_for_yield(0, -0.5);
    // periods_for_yield(-0.5, 0.5);
    // periods_for_yield(-0.5, 0);
    // periods_for_yield(-0.5, -0.5);
}


/* evidence_pattern: test pattern */
void evidence_pattern() {
    printf("*** testing pattern\n");

    printf("- expecting 3 sections of a grid with 5 rows and 4 columns\n");
    pattern(5, 4, 3);

    printf("- expecting 1 sections of a grid with 4 rows and 3 columns\n");
    pattern(4, 3, 1);

    printf("- expecting empty output\n");
    pattern(0, 2, 2);

    printf("- expecting 2 sections of a grid with 2 rows and empty columns\n");
    pattern(2, 0, 2);

    printf("- expecting empty output\n");
    pattern(2, 2, 0);

    printf("- expecting 4 sections of a grid with 7 rows and 11 columns\n");
    pattern(7, 11, 4);
}


/* main: run the evidence functions above */
int main(int argc, char *argv[]) {
    evidence_tens_letters();
    evidence_common_divisors();
    evidence_legal_keys();
    evidence_periods_for_yield();
    evidence_pattern();

    return 0;
}