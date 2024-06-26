#include <stdlib.h>
#include <stdio.h>
#include "hw1.h"

/* evidence_is_buoyant: test is_buoyant */
void evidence_is_buoyant() {
   printf("*** testing is_buoyant\n");
   /* tests */
   printf("- expecting 0: %d\n", is_buoyant(10000,2.7));
   printf("- expecting 1: %d\n", is_buoyant(200000,10));
   printf("- expecting 0: %d\n", is_buoyant(300000,10));
   printf("- expecting 1: %d\n", is_buoyant(0.05,0.1));
   printf("- expecting 0: %d\n", is_buoyant(0.5,0.1));
}

/* evidence_pods_to_order: test pods_to_order */
void evidence_pods_to_order() {
   printf("*** testing pods_to_order\n");
   /* tests */
   printf("- expecting 288: %u\n", pods_to_order(5,6,7));
   printf("- expecting 192: %u\n", pods_to_order(10,10,1));
   printf("- expecting 384: %u\n", pods_to_order(96,2,2));
   printf("- expecting 192: %u\n", pods_to_order(94,1,2));
   printf("- expecting 192: %u\n", pods_to_order(97,1,1));
   printf("- expecting 0: %u\n", pods_to_order(100,0,0));
   printf("- expecting 0: %u\n", pods_to_order(0,100,0));
   printf("- expecting 0: %u\n", pods_to_order(0,0,100));
}

/* evidence_gcd: test gcd */
void evidence_gcd() {
   printf("*** testing gcd\n");
   /* tests */
   printf("- expecting 1: %u\n", gcd(2,1));
   printf("- expecting 1: %u\n", gcd(7,2));
   printf("- expecting 9: %u\n", gcd(63,36));
   printf("- expecting 3: %u\n", gcd(9,6));
   printf("- expecting 8: %u\n", gcd(24,16));
   printf("- expecting 5: %u\n", gcd(5,5));
   printf("- expecting 26: %u\n", gcd(52,26));
   printf("- expecting 0: %u\n", gcd(0,0));
   printf("- expecting 5: %u\n", gcd(5,0));
}

/* main: run the evidence functions above */
int main(int argc, char *argv[]) {
   evidence_is_buoyant();
   evidence_pods_to_order();
   evidence_gcd();

   return 0;
}