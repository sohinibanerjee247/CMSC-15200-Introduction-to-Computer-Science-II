#include <stdlib.h>
#include <stdio.h>
#include "lab3.h"

/* evidence_graph: test graph */
void evidence_graph()
{
    printf("*** testing graph\n");

    printf("y = 0.1x^2 + 2, x = [-20, 20], y = [-1, 20], scale = 1\n");
    printf("vertex at (0, 2), opens up, 7 pts on y = 2\n");
    graph(0.1, 0, 2, 1, -20, 20, -1, 20);

    printf("y = x^2, x = [-3, 4], y = [-1, 16], scale = 1\n");
    printf("vertex at origin, opens up, 8 pts total\n");
    graph(1, 0, 0, 1, -3, 4, -1, 16);

    printf("y = x^2, x = [-1.5, 2], y = [-0.5, 8], scale = 0.5\n");
    printf("vertex at origin, opens up, 3 pts on x axis\n");
    graph(1, 0, 0, 0.5, -3, 4, -1, 16);

    printf("y = x^2, x = [-5, 5], y = [0, 25], scale = 1\n");
    printf("vertex at origin, opens up, 11 pts total\n");
    graph(1, 0, 0, 1, -5, 5, 0, 25);

    printf("y = 0.05^2, x = [-40, 40], y = [0, 85], scale = 1\n");
    printf("vertex at origin, opens up, 9 pts on x axis\n");
    graph(0.05, 0, 0, 1, -40, 40, 0, 85);

    printf("y = x^2 + 5x + 7, x = [-8, 3], y = [0, 35], scale = 1\n");
    printf("vertex not visible, opens up, 2 pts on y = 1\n");
    graph(1, 5, 7, 1, -8, 3, 0, 35);

    printf("y = x^2 + 6x + 7, x = [-9, 3], y = [-5, 35], scale = 1\n");
    printf("vertex at (-3, -2), opens up, 3 pts below x axis\n");
    graph(1, 6, 7, 1, -9, 3, -5, 35);

    printf("y = x^2 - 4x + 7, x = [1, 10], y = [0, 12], scale = 1\n");
    printf("vertex at (2, 3), opens up, 5 pts total, y axis not visible\n");
    graph(1, -4, 7, 1, 1, 10, 0, 12);

    printf("y = x^2 - 4x + 7, x = [1, 5], y = [0, 12], scale = 1\n");
    printf("same as prior graph but fewer positive x marks\n");
    graph(1, -4, 7, 1, 1, 5, 0, 12);

    printf("y = -x^2, x = [-2.5, 2.5], y = [-12.5, 0.5], scale = 0.5\n");
    printf("vertex at origin, opens down, 11 pts total\n");
    graph(-1, 0, 0, 0.5, -5, 5, -25, 1);

    printf("y = 0, x = [-5, 5], y = [-5, 5], scale = 1\n");
    printf("no parabola, horiz axis of stars, vert axis of marks\n");
    graph(0, 0, 0, 1, -5, 5, -5, 5);
}


/* main: run the evidence functions above */
int main(int argc, char *argv[])
{
    evidence_graph();
    return 0;
}