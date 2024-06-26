#include <stdlib.h>
#include <stdio.h>

/* Print character for current coordinates */
void print_item(double y_pred, double low_y, double high_y,
                double x_scaled, double y_scaled)
{
    if (y_pred >= low_y && y_pred < high_y) {
        printf("*");
    } else if (x_scaled == 0 && y_scaled == 0) {
        printf("+");
    } else if (x_scaled == 0) {
        printf("|");
    } else if (y_scaled == 0) {
        printf("-");
    } else {
        printf(" ");
    }
}


/* Calculate predicted y value */
double calc_y_value(double a, double b, double c, double x_scaled)
{
    return a * x_scaled * x_scaled + b * x_scaled + c;
}


void graph(double a, double b, double c, double step, int xleft, int xright,
           int ybottom, int ytop)
{
    for (int y = ytop; y >= ybottom; y--) {
        double y_scaled = y * step;

        double low_y = y_scaled;
        double high_y = y_scaled + step;

        for (int x = xleft; x <= xright; x++) {
            double x_scaled = x * step;

            double y_pred = calc_y_value(a, b, c, x_scaled);
            print_item(y_pred, low_y, high_y, x_scaled, y_scaled);
        }
        printf("\n");
    }
}
