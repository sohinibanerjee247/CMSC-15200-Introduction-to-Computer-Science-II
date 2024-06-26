/* tens_letters : counts unique letters for multiples of 10 in [0, 90] */
unsigned char tens_letters(unsigned char number);

/* common_divisors : common factors between two numbers */
void common_divisors(unsigned int n, unsigned int m);

/* legal_keys : counts legal keys for 4 cuts given depths and macs limit */
unsigned int legal_keys(unsigned char depths, unsigned char macs);

/* periods_for_yield : minimum periods to reach yield given specific rate */
unsigned int periods_for_yield(double rate, double yield);

/* pattern : ascii art pattern given side, width, and height size */
void pattern(unsigned char side, unsigned char width, unsigned char height);