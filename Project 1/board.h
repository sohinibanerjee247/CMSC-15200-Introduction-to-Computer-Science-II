#ifndef BOARD_H
#define BOARD_H

#include "pos.h"


enum cell {
    EMPTY,
    BLACK,
    WHITE
};

typedef enum cell cell;


union board_rep {
    enum cell** matrix;
    unsigned int* bits;
};

typedef union board_rep board_rep;


enum type {
    MATRIX, BITS
};


struct board {
    unsigned int width, height;
    enum type type;
    board_rep u;
};

typedef struct board board;


/* board_new: creates new board and assigns parameters */
board* board_new(unsigned int width, unsigned int height, enum type type);


/* board_free: frees memory allocated for board */
void board_free(board* b);


/* board_show: prints board with row and column headers */
void board_show(board* b);


/* board_get: returns cell of pos p in board */
cell board_get(board* b, pos p);


/* board_set: sets pos p in board to cell c */
void board_set(board* b, pos p, cell c);


#endif /* BOARD_H */
