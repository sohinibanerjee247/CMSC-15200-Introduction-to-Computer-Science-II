#include <stdlib.h>
#include <stdio.h>
#include "lab2.h"

/* evidence_expt: test expt */
void evidence_expt() {
   printf("*** testing expt\n");
   /* tests */
   printf("- expecting 1: %lld\n", expt(2,0));
   printf("- expecting 8: %lld\n", expt(2,3));
   printf("- expecting 1: %lld\n", expt(1,1));
   printf("- expecting 3125: %lld\n", expt(5,5));
   printf("- expecting 1: %lld\n", expt(0,0));
   printf("- expecting 64: %lld\n", expt(4,3));
   printf("- expecting 1000: %lld\n", expt(10,3));
   printf("- expecting -32: %lld\n", expt(-2,5));
   printf("- expecting -1: %lld\n", expt(-1,1));
   printf("- expecting 1: %lld\n", expt(-1,0));
   printf("- expecting 1296: %lld\n", expt(-6,4));
   printf("- expecting 129140163: %lld\n", expt(3,17));
}

/* evidence_ss: test ss */
void evidence_ss() {
   printf("*** testing ss\n");
   /* tests */
   printf("- expecting 1: %lld\n", ss(2,0));
   printf("- expecting 8: %lld\n", ss(2,3));
   printf("- expecting 1: %lld\n", ss(1,1));
   printf("- expecting 3125: %lld\n", ss(5,5));
   printf("- expecting 1: %lld\n", ss(0,0));
   printf("- expecting 64: %lld\n", ss(4,3));
   printf("- expecting 1000: %lld\n", ss(10,3));
   printf("- expecting -32: %lld\n", ss(-2,5));
   printf("- expecting -1: %lld\n", ss(-1,1));
   printf("- expecting 1: %lld\n", ss(-1,0));
   printf("- expecting 1296: %lld\n", ss(-6,4));
   printf("- expecting 129140163: %lld\n", ss(3,17));
}

/* evidence_ssm: test ssm */
void evidence_ssm() {
   printf("*** testing ssm\n");
   /* tests */
   printf("- expecting 1: %d\n", ssm(2,0,2));
   printf("- expecting 2: %d\n", ssm(2,3,3));
   printf("- expecting 0: %d\n", ssm(1,1,1));
   printf("- expecting 2: %d\n", ssm(5,5,3));
   printf("- expecting 0: %d\n", ssm(10,10,5));
   printf("- expecting 1: %d\n", ssm(10,6,7));
   printf("- expecting 6: %d\n", ssm(29,14,43));
   printf("- expecting 5: %d\n", ssm(4,7,11));
   printf("- expecting 0: %d\n", ssm(4,4,4));
   printf("- expecting 2: %d\n", ssm(8,17,31));
   printf("- expecting 391: %d\n", ssm(13,1099,726));
   printf("- expecting 5: %d\n", ssm(2,81,67));
   printf("- expecting 0: %d\n", ssm(2000,2000,5));
   printf("- expecting 3: %d\n", ssm(3,17,5));
}

/* main: run the evidence functions above */
int main(int argc, char *argv[]) {
   evidence_expt();
   evidence_ss();
   evidence_ssm();

   return 0;
}