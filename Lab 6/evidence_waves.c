#include <stdlib.h>
#include <stdio.h>
#include "waves.h"

int main(int argc, char *argv[]) {
    printf("- expecting 2.8284: %.4lf\n", dist(1, 2, 3, 4));
    printf("- expecting 26.5547: %.4lf\n", dist(-0.5, 0.15, 0.0002, 26.7));
    printf("- expecting 0.0000: %.4lf\n", dist(0, 0, 0, 0));
    printf("- expecting 0.0000: %.4lf\n", dist(100, 101, 100, 101));
    printf("- expecting 2.2361: %.4lf\n", dist(-5, -5, -3, -4));
    printf("- expecting 1.4142: %.4lf\n", dist(0, 0, 1, 1));
    return 0;
}