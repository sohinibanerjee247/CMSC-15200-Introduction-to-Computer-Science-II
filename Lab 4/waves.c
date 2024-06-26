#include <stdlib.h>
#include <stdio.h>
#include <math.h>

double dist(double x0, double y0, double x1, double y1) {
    return sqrt(pow(x0 - x1, 2) + pow(y0 - y1, 2));
}


/* find_center: finds center given side length */
int find_center(int side_length) {
    return side_length / 2;
}


/* find_offset_center: finds offset center given center and offset */
int find_offset_center(int center, int offset) {
    return center + offset;
}


/* print_header: prints ppm file header */
void print_header(int side_length, unsigned char max) {
    printf("P3\n");
    printf("%d %d\n", side_length, side_length);
    printf("%hhu\n", max);
}


/* find_b: finds b value given current position and offset */
unsigned char find_b(int x, int y, int x_offset_center, int y_offset_center,
                     unsigned char max) {
    double distance = dist(x, y, x_offset_center, y_offset_center);
    double sin_distance = sin(distance);
    return (sin_distance + 1) * max / 2;
}


void draw_waves(int side_length, int x_offset, int y_offset) {
    if (side_length <= 0) {
        fprintf(stderr, "draw_waves: error - side length %d is not positive\n",
                side_length);
        exit(1);
    }

    unsigned char max = 255;
    int center = find_center(side_length);
    int x_offset_center = find_offset_center(center, x_offset);
    int y_offset_center = find_offset_center(center, y_offset);

    print_header(side_length, max);

    for (int y = 0; y < side_length; y++) {
        for (int x = 0; x < side_length; x++) {
            unsigned char b = find_b(x, y, x_offset_center, y_offset_center,
                                     max);
            printf("0 0 %hhu\n", b);
        }
    }
}