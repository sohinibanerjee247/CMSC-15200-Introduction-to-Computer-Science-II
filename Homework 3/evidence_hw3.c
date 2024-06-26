#include <stdlib.h>
#include <stdio.h>
#include "hw3.h"

/* print_unsigned_int_array: prints unsigned int array */
void print_unsigned_int_array(unsigned int a[], unsigned int alen) {
    if (alen > 0) {
        unsigned int i = 0;
        for (i = 0; i < alen - 1; i++) {
            printf("%u ", a[i]);
        }
        printf("%u", a[i]);
    }
    printf("\n");
}


/* print_int_array: prints int array */
void print_int_array(int a[], unsigned int alen) {
    if (alen > 0) {
        unsigned int i = 0;
        for (i = 0; i < alen - 1; i++) {
            printf("%d ", a[i]);
        }
        printf("%d", a[i]);
    }
    printf("\n");
}


/* evidence_all_positive: test all_positive */
void evidence_all_positive() {
    printf("*** testing all_positive\n");

    int a[] = {1, 2, 3, 4};
    printf("- expecting 1: %d\n", all_positive(a, 4));

    int b[] = {};
    printf("- expecting 1: %d\n", all_positive(b, 0));

    int c[] = {1, 2, -3, 0};
    printf("- expecting 0: %d\n", all_positive(c, 4));
}


/* evidence_exists_positive: test exists_positive */
void evidence_exists_positive() {
    printf("*** testing exists_positive\n");

    int a[] = {1, 2, 3, 4};
    printf("- expecting 1: %d\n", exists_positive(a, 4));

    int b[] = {};
    printf("- expecting 0: %d\n", exists_positive(b, 0));

    int c[] = {0, -1, -2};
    printf("- expecting 0: %d\n", exists_positive(c, 3));
}


/* evidence_first_positive: test first_positive */
void evidence_first_positive() {
    printf("*** testing first_positive\n");

    int a[] = {-1, 0, 3, 4};
    printf("- expecting 2: %d\n", first_positive(a, 4));

    int b[] = {-1, -5, 0, -2};
    printf("- expecting -1: %d\n", first_positive(b, 4));

    int c[] = {};
    printf("- expecting -1: %d\n", first_positive(c, 0));
}


/* evidence_number_positives: test number_positives */
void evidence_number_positives() {
    printf("*** testing number_positives\n");

    int a[] = {-1, 2, 0, -4, 4, 2};
    printf("- expecting 3: %d\n", number_positives(a, 6));

    int b[] = {};
    printf("- expecting 0: %d\n", number_positives(b, 0));
}


/* evidence_negate: test negate */
void evidence_negate() {
    printf("*** testing negate\n");
    
    int a[] = {-1, 2, 0, -4, 4, 2};
    printf("- expecting 1 -2 0 4 -4 -2: ");
    negate(a, 6);
    print_int_array(a, 6);

    int b[] = {};
    printf("- expecting no output:");
    negate(b, 0);
    print_int_array(b, 0);
}


/* evidence_partial_sums: test partial_sums */
void evidence_partial_sums() {
    printf("*** testing partial_sums\n");

    int a[] = {-1, 2, 0, -4, 4, 2};
    printf("- expecting 0 -1 1 1 -3 1 3: ");
    int* ares = partial_sums(a, 6);
    print_int_array(ares, 7);
    free(ares);

    int b[] = {};
    printf("- expecting 0: ");
    int* bres = partial_sums(b, 0);
    print_int_array(bres, 1);
    free(bres);
}


/* evidence_reverse: test reverse */
void evidence_reverse() {
    printf("*** testing reverse\n");
    int a[] = {-1, 2, 0, -4, 4, 2};
    printf("- expecting 2 4 -4 0 2 -1: ");
    reverse(a, 6);
    print_int_array(a, 6);

    int b[] = {-4, -3, 0, 1, 6, 7, 10};
    printf("- expecting 10 7 6 1 0 -3 -4: ");
    reverse(b, 7);
    print_int_array(b, 7);

    int c[] = {};
    printf("- expecting no output:");
    reverse(c, 0);
    print_int_array(c, 0);
}


/* evidence_merge: test merge */
void evidence_merge() {
    printf("*** testing merge\n");

    int a[] = {-4, -3, 0, 1, 6, 7, 10};
    int b[] = {-9, -3, -3, 2, 11};
    printf("- expecting -9 -4 -3 -3 -3 0 1 2 6 7 10 11: ");
    int* abres = merge(a, 7, b, 5);
    print_int_array(abres, 12);
    free(abres);

    int c[] = {1, 2, 3, 4, 5, 6, 7, 8};
    int d[] = {1, 2, 3, 4, 5, 9};
    printf("- expecting 1 1 2 2 3 3 4 4 5 5 6 7 8 9: ");
    int *cdres = merge(c, 8, d, 6);
    print_int_array(cdres, 14);
    free(cdres);

    int e[] = {};
    int f[] = {};
    printf("- expecting no output:");
    int* efres = merge(e, 0, f, 0);
    print_int_array(efres, 0);
    free(efres);
}


/* evidence_primes_in_range: test primes_in_range */
void evidence_primes_in_range() {
    printf("*** testing primes_in_range\n");
    unsigned int len;

    printf("- expecting 2 3 5 7: ");
    unsigned int* ares = primes_in_range(1, 10, &len);
    print_unsigned_int_array(ares, len);
    free(ares);

    printf("- expecting 23 29 31 37 41 43 47 53 59 61 67 71 73: ");
    unsigned int* bres = primes_in_range(20, 75, &len);
    print_unsigned_int_array(bres, len);
    free(bres);

    printf("- expecting no output:");
    unsigned int* cres = primes_in_range(20, 22, &len);
    print_unsigned_int_array(cres, len);
    free(cres);

    printf("- expecting 2 3: ");
    unsigned int* dres = primes_in_range(0, 3, &len);
    print_unsigned_int_array(dres, len);
    free(dres);
}


/* main: run the evidence functions above */
int main(int argc, char *argv[]) {
    evidence_all_positive();
    evidence_exists_positive();
    evidence_first_positive();
    evidence_number_positives();
    evidence_negate();
    evidence_partial_sums();
    evidence_reverse();
    evidence_merge();
    evidence_primes_in_range();

    return 0;
}