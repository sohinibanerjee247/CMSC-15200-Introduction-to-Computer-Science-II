/* all_positive: checks if all numbers in array are positive */
int all_positive(int a[], unsigned int alen);

/* exists_positive: checks if positive number exists in array */
int exists_positive(int a[], unsigned int alen);

/* first_positive: returns index of first positive number, -1 otherwise */
int first_positive(int a[], unsigned int alen);

/* number_positives: returns number of positive numbers in array */
unsigned int number_positives(int a[], unsigned int alen);

/* negate: negates numbers in array */
void negate(int a[], unsigned int alen);

/* partial_sums: returns partial sums of array */
int* partial_sums(int a[], unsigned int alen);

/* reverse: reverses numbers in array */
void reverse(int a[], unsigned int alen);

/* merge: merges two ordered arrays together in order */
int* merge(int* a, unsigned int alen, int* b, unsigned int blen);

/* primes_in_range: returns array of prime numbers in range */
unsigned int* primes_in_range(unsigned int lb, unsigned int ub,
                              unsigned int* len);