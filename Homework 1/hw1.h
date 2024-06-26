/* is_buoyant : whether spherical object floats in water */
int is_buoyant(double weight, double radius);

/* pods_to_order : number of pods to buy */
unsigned int pods_to_order(unsigned int people, unsigned int cups_per_day,
                           unsigned int days);

/* gcd : greatest common divisor with Euclid's algorithm */
unsigned int gcd(unsigned int n, unsigned int m);