#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "waves.h"

int main(int argc, char *argv[]) {
    int side_length = 200, x_offset = 0, y_offset = 0;
    double scale_red = 1.0, scale_green = 1.0, scale_blue = 1.0;

    char *command, *value;
    for (unsigned int arg = 1; arg < argc; arg += 2) {
        command = argv[arg];

        if (command[0] == '-') {
            value = argv[arg + 1];
            switch (command[1]) {
                case 's':
                    side_length = atoi(value);
                    break;
                case 'r':
                    scale_red = atof(value);
                    break;
                case 'g':
                    scale_green = atof(value);
                    break;
                case 'b':
                    scale_blue = atof(value);
                    break;
                case 'x':
                    x_offset = atoi(value);
                    break;
                case 'y':
                    y_offset = atoi(value);
                    break;
                }
        }
    }
    draw_waves(side_length, x_offset, y_offset,
               scale_red, scale_green, scale_blue);

    return 0;
}