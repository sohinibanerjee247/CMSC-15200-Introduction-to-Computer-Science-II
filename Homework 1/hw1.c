#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int is_buoyant(double weight, double radius) {
   double volume = (4.0 / 3.0) * M_PI * pow(radius, 3);
   double force = volume * 62.4;
   return force >= weight;
}

unsigned int pods_to_order(unsigned int people, unsigned int cups_per_day,
                           unsigned int days) {
   unsigned int total_cups = people * cups_per_day * days;
   return (total_cups / 96 + (total_cups % 96 > 0)) * 96;
}

unsigned int gcd(unsigned int n, unsigned int m) {
   if (m == 0) {
      return n;
   }
   return gcd(m, n % m);
}