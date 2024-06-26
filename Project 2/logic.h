#ifndef LOGIC_H
#define LOGIC_H

#include <stdbool.h>
#include "board.h"


/* turn: BLACK or WHITE turn in game */
enum turn {
    BLACKS_TURN,
    WHITES_TURN
};

typedef enum turn turn;


/* outcome: game status of progress, black/white win, or draw */
enum outcome {
    IN_PROGRESS,
    BLACK_WIN,
    WHITE_WIN,
    DRAW
};

typedef enum outcome outcome;


/* game: board, player, and magnet info/status */
struct game {
    unsigned int square, maglock, black_rem, white_rem;
    board* b;
    turn player;
};

typedef struct game game;


/* new_game: creates new game and assigns parameters */
game* new_game(unsigned int square, unsigned int maglock, unsigned int width,
               unsigned int height, enum type type);


/* game_free: frees memory allocated for game */
void game_free(game* g);


/* drop_piece: drops piece in specified column, if possible */
bool drop_piece(game* g, unsigned int column);


/* magnetize: magnetizes board */
bool magnetize(game* g);


/* game_outcome: returns IN_PROGRESS, BLACK_WIN, WHITE_WIN, or DRAW status */
outcome game_outcome(game* g);


/* swap_pos: switches cells of two positions */
void swap_pos(game* g, pos swap, pos current, cell color);


#endif /* LOGIC_H */