#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "pos.h"
#include "board.h"
#include "logic.h"


/* get_column: converts char col input to column index number */
unsigned int get_column(char col, unsigned digits, unsigned int letters) {
    if (col >= '0' && col <= '9') {
        return col - '0';
    } else if (col >= 'A' && col <= 'Z') {
        return col - 'A' + digits;
    } else {
        return col - 'a' + digits + letters;
    }
}


/* is_valid_input: returns whether char col is a valid request */
bool is_valid_input(char col) {
    return (col >= '0' && col <= '9') || (col >= 'A' && col <= 'z')
           || col == '!';
}


/* main: run the evidence functions above */
int main(int argc, char *argv[]) {
    unsigned int s, l, w, h;
    enum type t;
    bool s_found = false, l_found = false, w_found = false, h_found = false,
         t_found = false;

    char *command, *value;
    for (unsigned int arg = 1; arg < argc; arg += 2) {
        command = argv[arg];

        if (command[0] == '-') {
            if (command[1] == 'm') {
                t = MATRIX;
                arg--;
                t_found = true;
                continue;
            }
            if (command[1] == 'b') {
                t = BITS;
                arg--;
                t_found = true;
                continue;
            }

            value = argv[arg + 1];
            switch (command[1]) {
                case 's':
                    s = atoi(value);
                    s_found = true;
                    break;
                case 'l':
                    l = atoi(value);
                    l_found = true;
                    break;
                case 'w':
                    w = atoi(value);
                    w_found = true;
                    break;
                case 'h':
                    h = atoi(value);
                    h_found = true;
            }
        }
    }

    if (!s_found || !l_found || !w_found || !h_found || !t_found) {
        fprintf(stderr, "error - not all parameters specified\n");
        exit(1);
    }

    unsigned int digits = 10;
    unsigned int letters = 'Z' - 'A' + 1;
    if (w > digits + 2 * letters || h > digits + 2 * letters) {
        fprintf(stderr, "error - board dim exceeds # of col names\n");
        exit(1);
    }

    game* g = new_game(s, l, w, h, t);
    char move;
    bool res;
    int col;
    while (game_outcome(g) == IN_PROGRESS) {
        board_show(g->b);
        do {
            res = false;
            if (g->player == BLACKS_TURN) {
                printf("Black: ");
            } else {
                printf("White: ");
            }
            scanf("%c%*c", &move);
            if (!is_valid_input(move)) {
                printf("try again - move input not valid\n");
            } else {
                if (move == '!') {
                    res = magnetize(g);
                    if (!res) {
                        printf("try again - magnet already on\n");
                    }
                } else {
                    col = get_column(move, digits, letters);
                    res = drop_piece(g, col);
                    if (!res) {
                        printf("try again - drop_piece input not valid\n");
                    }
                }
            }
        } while (!res);
    }
    board_show(g->b);
    int status = game_outcome(g);
    if (status == DRAW) {
        printf("DRAW\n");
    } else if (status == BLACK_WIN) {
        printf("BLACK WINS\n");
    } else if (status == WHITE_WIN) {
        printf("WHITE WINS\n");
    }
    game_free(g);

    return 0;
}