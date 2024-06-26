#include <stdlib.h>
#include <stdio.h>

int all_positive(int a[], unsigned int alen) {
    for (unsigned int i = 0; i < alen; i++) {
        if (a[i] <= 0) {
            return 0;
        }
    }
    return 1;
}


int exists_positive(int a[], unsigned int alen) {
    for (unsigned int i = 0; i < alen; i++) {
        if (a[i] > 0) {
            return 1;
        }
    }
    return 0;
}


int first_positive(int a[], unsigned int alen) {
    for (unsigned int i = 0; i < alen; i++) {
        if (a[i] > 0) {
            return i;
        }
    }
    return -1;
}


unsigned int number_positives(int a[], unsigned int alen) {
    unsigned int total_pos = 0;
    for (unsigned int i = 0; i < alen; i++) {
        total_pos += a[i] > 0;
    }
    return total_pos;
}


void negate(int a[], unsigned int alen) {
    for (unsigned int i = 0; i < alen; i++) {
        a[i] *= -1;
    }
}


int* partial_sums(int a[], unsigned int alen) {
    int* res = (int*)malloc((alen + 1) * sizeof(int));
    res[0] = 0;
    for (unsigned int i = 1; i <= alen; i++) {
        res[i] = res[i - 1] + a[i - 1];
    }
    return res;
}


/* swap: swaps values of two integers */
void swap(int* a, int* b) {
    int swap = *a;
    *a = *b;
    *b = swap;
}


void reverse(int a[], unsigned int alen) {
    for (unsigned int i = 0; i < alen / 2; i++) {
        swap(&a[i], &a[alen - i - 1]);
    }
}


int* merge(int* a, unsigned int alen, int* b, unsigned int blen) {
    int* res = (int*)malloc((alen + blen) * sizeof(int));
    unsigned int a_index = 0, b_index = 0;
    for (unsigned int i = 0; i < alen + blen; i++) {
        if (b_index >= blen || (a_index < alen && a[a_index] < b[b_index])) {
            res[i] = a[a_index++];
        } else {
            res[i] = b[b_index++];
        }
    }
    return res;
}


/* is_prime: returns whether number is prime */
int is_prime(unsigned int n) {
    for (unsigned int i = 2; i < n; i++) {
        if (n % i == 0) {
            return 0;
        }
    }
    return n != 1 && n != 0;
}


/* count_primes: returns number of prime numbers in range */
unsigned int count_primes(unsigned int lb, unsigned int ub) {
    unsigned int num_primes = 0;
    for (unsigned int i = lb; i <= ub; i++) {
        num_primes += is_prime(i);
    }
    return num_primes;
}


unsigned int* primes_in_range(unsigned int lb, unsigned int ub,
                              unsigned int* len) {
    unsigned int num_primes = count_primes(lb, ub);

    unsigned int* res = (unsigned int*)malloc(num_primes * sizeof(int));
    unsigned int res_index = 0;
    for (unsigned int i = lb; i <= ub; i++) {
        if (is_prime(i)) {
            res[res_index++] = i;
        }
    }

    *len = num_primes;
    return res;
}