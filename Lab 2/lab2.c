#include <stdlib.h>
#include <stdio.h>

long long int expt(int a, unsigned int n) {
   if (n == 0) {
      return 1;
   }
   return a * expt(a, n - 1);
}

long long int ss(int a, unsigned int n) {
   if (n == 0) {
      return 1;
   } else if (n % 2 == 0) {
      long long int temp = ss(a, n / 2);
      return temp * temp;
   } else {
      return a * ss(a, n - 1);
   }
}

int ssm(int a, unsigned int n, unsigned int m) {
   if (n == 0) {
      return 1;
   } else if (n % 2 == 0) {
      int temp = ssm(a, n / 2, m) % m;
      return temp * temp % m;
   } else {
      return a * (ssm(a, n - 1, m) % m) % m;
   }
}