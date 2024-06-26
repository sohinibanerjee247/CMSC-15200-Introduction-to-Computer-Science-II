#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "pos.h"
#include "board.h"
#include "logic.h"


game* new_game(unsigned int square, unsigned int maglock, unsigned int width,
               unsigned int height, enum type type) {
    game* g = (game*)malloc(sizeof(game));
    if (g == NULL) {
        fprintf(stderr, "new_game error - game not allocated\n");
        exit(1);
    }

    if (square * square > width * height) {
        fprintf(stderr, "new_game error - square size larger than board\n");
        exit(1);
    }

    g->square = square;
    g->maglock = maglock;
    g->black_rem = 0;
    g->white_rem = 0;
    g->b = board_new(width, height, type);
    g->player = BLACKS_TURN;
    return g;
}


void game_free(game* g) {
    board_free(g->b);
    free(g);
}


void swap_pos(game* g, pos swap, pos current, cell color) {
    board_set(g->b, current, EMPTY);
    board_set(g->b, swap, color);
}


/* current_player_rem: number of remaining turns player is on maglock */
unsigned int current_player_rem(game* g) {
    switch (g->player) {
    case BLACKS_TURN:
        return g->black_rem;
    case WHITES_TURN:
        return g->white_rem;
    }
}


/* change_turn: switches player turn */
void change_turn(game *g) {
    switch (g->player) {
    case BLACKS_TURN:
        g->player = WHITES_TURN;
        break;
    case WHITES_TURN:
        g->player = BLACKS_TURN;
    }
}


/* make_current_pos: returns current pos based on horiz or vert direction */
pos make_current_pos(unsigned int dim1, unsigned int dim2, char dir) {
    if (dir == 'H') {
        return make_pos(dim1, dim2);
    } else {
        return make_pos(dim2, dim1);
    }
}


/* slide: pushes all pieces of specified color to left, right, or down */
bool slide(game* g, cell color, int start1, int end1, int start2, int end2,
           int d1, int d2, char dir) {
    bool changed = false;

    for (int dim1 = start1; dim1 != end1; dim1 += d1) {
        for (int dim2 = start2; dim2 != end2; dim2 += d2) {
            pos current = make_current_pos(dim1, dim2, dir);
            if (board_get(g->b, current) == color) {
                int bound = dim2;
                while (bound != start2
                        && board_get(g->b,
                                     make_current_pos(dim1, bound - d2,
                                                      dir)) == EMPTY) {
                    bound -= d2;
                }
                pos swap = make_current_pos(dim1, bound, dir);
                if (current.r != swap.r || current.c != swap.c) {
                    swap_pos(g, swap, current, color);
                    changed = true;
                }
            }
        }
    }
    return changed;
}


/* end_magnetize: stops magnetize by collapsing hover and
other pieces (if its magnet is not on) */
void end_magnetize(game* g, cell hover, cell other,
                   bool* hover_change, bool* other_change) {
    *hover_change = slide(g, hover, 0, g->b->width,
                          g->b->height - 1, -1, 1, -1, 'V');

    switch (other) {
    case BLACK:
        if (g->black_rem == 0) {
            *other_change = slide(g, other, 0,
                                  g->b->width, g->b->height - 1, -1, 1, -1,
                                  'V');
        }
        break;
    case WHITE:
        if (g->white_rem == 0) {
            *other_change = slide(g, other, 0,
                                  g->b->width, g->b->height - 1, -1, 1, -1,
                                  'V');
        }
        break;
    case EMPTY:
        fprintf(stderr, "end_magnetize error - EMPTY cell invalid\n");
        exit(1);
    }
}


/* enable_end_magnetize: stops magnetize until no changes occur */
void enable_end_magnetize(game* g, cell hover, cell other) {
    bool hover_change, other_change;
    do {
        hover_change = false;
        other_change = false;
        end_magnetize(g, hover, other, &hover_change, &other_change);
    } while (hover_change || other_change);
}


/* find_next_turn: sets turn to next appropriate player */
void find_next_turn(game* g) {
    change_turn(g);
    while (current_player_rem(g) != 0) {
        switch (g->player) {
        case BLACKS_TURN:
            g->black_rem--;
            if (g->black_rem == 0) {
                enable_end_magnetize(g, BLACK, WHITE);
            }
            break;
        case WHITES_TURN:
            g->white_rem--;
            if (g->white_rem == 0) {
                enable_end_magnetize(g, WHITE, BLACK);
            }
        }
        change_turn(g);
    }
}


bool drop_piece(game* g, unsigned int column) {
    if (column >= g->b->width) {
        return false;
    }

    int r = -1;
    while (r + 1 < g->b->height && board_get(g->b,
            make_pos(r + 1, column)) == EMPTY) {
        r++;
    }
    if (r < 0) {
        return false;
    }

    switch (g->player) {
    case BLACKS_TURN:
        board_set(g->b, make_pos(r, column), BLACK);
        break;
    case WHITES_TURN:
        board_set(g->b, make_pos(r, column), WHITE);
    }

    find_next_turn(g);
    return true;
}


/* post_magnet_collapse: collapses non-magnet color if its magnet is not on */
bool post_magnet_collapse(game* g, cell color) {
    bool piece_collapse = false;
    switch (color) {
    case BLACK:
        if (g->white_rem == 0) {
            piece_collapse = slide(g, WHITE, 0, g->b->width,
                                   g->b->height - 1, -1, 1, -1, 'V');
        }
        break;
    case WHITE:
        if (g->black_rem == 0) {
            piece_collapse = slide(g, BLACK, 0, g->b->width,
                                   g->b->height - 1, -1, 1, -1, 'V');
        }
        break;
    case EMPTY:
        fprintf(stderr, "post_magnet_collapse error - EMPTY cell invalid\n");
        exit(1);
    }
    return piece_collapse;
}


/* turn_magnet_on: turns magnet on until no changes occur */
void turn_magnet_on(game* g, int c_start, int c_end, int dc, cell color) {
    bool piece_magnetize, piece_collapse;
    do {
        piece_magnetize = slide(g, color, 0, g->b->height,
                                c_start, c_end, 1, dc, 'H');
        piece_collapse = post_magnet_collapse(g, color);
    } while (piece_magnetize || piece_collapse);
}


bool magnetize(game* g) {
    switch (g->player) {
    case BLACKS_TURN:
        if (g->black_rem > 0) {
            return false;
        }
        turn_magnet_on(g, 0, g->b->width, 1, BLACK);
        g->black_rem = g->maglock;
        if (g->black_rem == 0) {
            enable_end_magnetize(g, BLACK, WHITE);
        }
        break;
    case WHITES_TURN:
        if (g->white_rem > 0) {
            return false;
        }
        turn_magnet_on(g, g->b->width - 1, -1, -1, WHITE);
        g->white_rem = g->maglock;
        if (g->white_rem == 0) {
            enable_end_magnetize(g, WHITE, BLACK);
        }
    }

    find_next_turn(g);
    return true;
}


/* board_filled: returns if board has black or white piece in all spots */
bool board_filled(game* g) {
    unsigned int total_empty = 0;
    for (unsigned int r = 0; r < g->b->height; r++) {
        for (unsigned int c = 0; c < g->b->width; c++) {
            pos p = make_pos(r, c);
            total_empty += board_get(g->b, p) == EMPTY;
        }
    }
    return total_empty == 0;
}


/* assign_outcome: returns outcome based on black and white square status */
outcome assign_outcome(game* g, bool black_sq, bool white_sq) {
    bool filled = board_filled(g);
    if ((black_sq && white_sq) || filled) {
        return DRAW;
    }
    if (black_sq) {
        return BLACK_WIN;
    }
    if (white_sq) {
        return WHITE_WIN;
    }
    return IN_PROGRESS;
}


/* check_square: checks if square in bounds has all black or all white */
void check_square(game* g, bool* black_sq, bool* white_sq,
                  unsigned int r, unsigned int c, unsigned int sq_area) {
    unsigned int black_piece = 0;
    unsigned int white_piece = 0;

    for (unsigned int r_sq = r; r_sq < r + g->square; r_sq++) {
        for (unsigned int c_sq = c; c_sq < c + g->square; c_sq++) {
            pos p = make_pos(r_sq, c_sq);
            cell color = board_get(g->b, p);
            black_piece += (color == BLACK);
            white_piece += (color == WHITE);

            if (black_piece > 0 && white_piece > 0) {
                return;
            }
        }
    }
    *black_sq = *black_sq || black_piece == sq_area;
    *white_sq = *white_sq || white_piece == sq_area;
}


outcome game_outcome(game* g) {
    unsigned int sq_area = g->square * g->square;
    unsigned int r_max_start = g->b->height - g->square;
    unsigned int c_max_start = g->b->width - g->square;
    bool black_sq = false;
    bool white_sq = false;

    for (unsigned int r = 0; r <= r_max_start; r++) {
        for (unsigned int c = 0; c <= c_max_start; c++) {
            check_square(g, &black_sq, &white_sq, r, c, sq_area);
        }
    }
    return assign_outcome(g, black_sq, white_sq);
}
