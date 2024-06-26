#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "pos.h"
#include "board.h"
#include "logic.h"


pos make_pos(unsigned int r, unsigned int c) {
    pos p;
    p.r = r;
    p.c = c;
    return p;
}