#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "pos.h"
#include "board.h"
#include "logic.h"


/* test_make_pos: tests make_pos function */
void test_make_pos() {
    printf("----- test_make_pos -----\n");
    pos p1 = make_pos(2, 3);
    printf("expecting 2, 3: %u, %u\n", p1.r, p1.c);

    pos p2 = make_pos(3, 100);
    printf("expecting 3, 100: %u, %u\n", p2.r, p2.c);
}


/* display_game_result: prints game outcome in words */
void test_game_outcome(game* g, char* expect) {
    printf("%s", expect);
    int status = game_outcome(g);
    if (status == DRAW) {
        printf("DRAW\n");
    } else if (status == BLACK_WIN) {
        printf("BLACK WINS\n");
    } else if (status == WHITE_WIN) {
        printf("WHITE WINS\n");
    }
}


/* display: prints expected message and board */
void display(board* b, char* expect, bool result) {
    printf("%s\nSUCCESS = %d\n", expect, result);
    board_show(b);
}


/* test_board_new: tests board_new function */
void test_board_new(enum type t) {
    printf("----- test_board_new -----\n");
    printf("expecting: width = 5, height = 4, type = %u\n", t);
    board* b1 = board_new(5, 4, t);
    printf("width = %u, height = %u, type = %u\n",
           b1->width, b1->height, b1->type);
    board_free(b1);

    /*printf("expecting: board_new error - 0 dim board not allowed\n");
    board* b2 = board_new(0, 1, t);
    board_free(b2);*/
}


/* test_header: tests header items for game */
void test_header(enum type t) {
    printf("----- test_header -----\n");
    game* g = new_game(2, 2, 50, 75, t);
    printf("expecting:\nrows 0-9, A-Z, a-z, ? for rest\ncols 0-9, A-Z, a-n\n");
    board_show(g->b);
    game_free(g);
}


/* test_board_set: tests board_set function */
void test_board_set(enum type t) {
    printf("----- test_board_set -----\n");
    game* g = new_game(2, 2, 5, 4, t);
    board_set(g->b, make_pos(3, 2), WHITE);
    printf("expecting: white o in row 3, col 2\n");
    board_show(g->b);

    board_set(g->b, make_pos(2, 2), BLACK);
    printf("expecting: black * in row 2, col 2\n");
    board_show(g->b);

    /*board_set(g->b, make_pos(5, 2), BLACK);
    printf("expecting: board_set error - row out of bounds\n");
    board_show(g->b);*/

    game_free(g);
}


/* test_board_get: tests board_get function */
void test_board_get(enum type t) {
    printf("----- test_board_get -----\n");
    game* g = new_game(2, 2, 5, 4, t);
    pos p1 = make_pos(3, 2);
    pos p2 = make_pos(2, 2);
    pos p3 = make_pos(3, 3);

    board_set(g->b, p1, WHITE);
    board_set(g->b, p2, BLACK);
    board_set(g->b, p3, EMPTY);

    printf("expecting 2 (WHITE): %u\n", board_get(g->b, p1));
    printf("expecting 1 (BLACK): %u\n", board_get(g->b, p2));
    printf("expecting 0 (EMPTY): %u\n", board_get(g->b, p3));
    /*pos p4 = make_pos(5, 5);
    printf("expecting: board_get error - row out of bounds\n");
    board_get(g->b, p4);*/

    game_free(g);
}


/* test_swap_pos: tests swap_pos function */
void test_swap_pos(enum type t) {
    printf("----- test_swap_pos -----\n");
    game* g = new_game(3, 3, 5, 5, t);
    pos current = make_pos(2, 3);
    pos swap = make_pos(2, 4);
    board_set(g->b, current, BLACK);
    swap_pos(g, swap, current, BLACK);

    printf("expecting:\n"
           ".....\n.....\n....*\n.....\n.....\n");
    board_show(g->b);
    game_free(g);
}


/* test_drop_piece: tests drop_piece function */
void test_drop_piece(enum type t) {
    printf("----- test_drop_piece -----\n");
    game* g = new_game(2, 2, 5, 4, t);
    bool success;

    success = drop_piece(g, 3);
    display(g->b, "expecting: black * in row 3, col 3, success = 1\n", success);

    success = drop_piece(g, 3);
    display(g->b, "expecting: white o in row 2, col 3, success = 1\n", success);

    success = drop_piece(g, 3);
    display(g->b, "expecting: black * in row 1, col 3, success = 1\n", success);

    success = drop_piece(g, 3);
    display(g->b, "expecting: white o in row 0, col 3, success = 1\n", success);

    success = drop_piece(g, 3);
    display(g->b, "expecting: no change, success = 0\n", success);

    game_free(g);
}


/* test_magnetize: tests magnetize function */
void test_magnetize(enum type t) {
    printf("----- test_magnetize -----\n");
    bool success;

    game* g1 = new_game(2, 2, 3, 3, t);
    success = drop_piece(g1, 0);
    success = drop_piece(g1, 0);
    success = drop_piece(g1, 0);
    success = magnetize(g1);
    display(g1->b, "expecting white magnetize:\nsuccess = 1\n...\n*.o\n*..\n",
            success);
    game_free(g1);

    game* g2 = new_game(2, 1, 5, 4, t);
    success = drop_piece(g2, 1);
    success = drop_piece(g2, 3);
    success = drop_piece(g2, 3);
    success = drop_piece(g2, 2);
    success = drop_piece(g2, 2);
    success = drop_piece(g2, 2);
    success = drop_piece(g2, 2);
    success = magnetize(g2);
    display(g2->b, "expecting white magnetize:\n"
            "success = 1\n.....\n....o\n..**.\n.**oo\n", success);
    success = magnetize(g1);
    display(g2->b, "expecting white magnetize:\n"
            "success = 1\n.....\n.....\n**..o\n**.oo\n", success);
    game_free(g2);

}


/* test_new_game: tests new_game function */
void test_new_game(enum type t) {
    printf("----- test_new_game -----\n");
    printf("expecting: square = 2, maglock = 3, "
           "black_rem = 0, white_rem = 0, player = 0 (BLACKS_TURN)\n");
    game* g1 = new_game(2, 3, 2, 3, t);
    printf("square = %u, maglock = %u, "
           "black_rem = %u, white_rem = %u, player = %u\n",
           g1->square, g1->maglock, g1->black_rem, g1->white_rem, g1->player);
    game_free(g1);

    /*printf("expecting: new_game error - square size larger than board\n");
    game* g2 = new_game(8, 4, 5, 5, t);
    game_free(g2);*/
}


/* game1: simulates game1 - includes invalid move and magnetize */
void game1(enum type t) {
    printf("----- game1 -----\n");
    game* g = new_game(2, 2, 5, 4, t);
    bool success;

    display(g->b, "expecting: row 0-3 and col 0-4\n", g->b != NULL);

    success = drop_piece(g, 3);
    display(g->b, "expecting: black * in row 3, col 3, success = 1\n", success);

    success = drop_piece(g, 3);
    display(g->b, "expecting: white o in row 2, col 3, success = 1\n", success);

    success = drop_piece(g, 3);
    display(g->b, "expecting: black * in row 1, col 3, success = 1\n", success);

    success = drop_piece(g, 3);
    display(g->b, "expecting: white o in row 0, col 3, success = 1\n", success);

    success = drop_piece(g, 3);
    display(g->b, "expecting: no change, success = 0\n", success);

    success = drop_piece(g, 1);
    display(g->b, "expecting: black * in row 3, col 1, success = 1\n", success);

    success = drop_piece(g, 0);
    display(g->b, "expecting: white o in row 3, col 0, success = 1\n", success);

    success = drop_piece(g, 1);
    display(g->b, "expecting: black * in row 2, col 1, success = 1\n", success);

    success = drop_piece(g, 1);
    display(g->b, "expecting: white o in row 1, col 1, success = 1\n", success);

    success = magnetize(g);
    display(g->b, "expecting black magnetize:\nsuccess = 1\n"
            ".....\n*....\n*o.o.\no**o.\n", success);

    success = drop_piece(g, 4);
    display(g->b, "expecting: white o in row 3, col 4, success = 1\n", success);

    success = magnetize(g);
    display(g->b, "expecting white magnetize:\nsuccess = 1\n"
            ".....\n*....\n*..oo\no**oo\n", success);

    test_game_outcome(g, "expecting WHITE WINS: ");

    game_free(g);
}


/* game2: simulates game2 - includes draw result */
void game2(enum type t) {
    printf("----- game2 -----\n");
    game* g = new_game(2, 2, 2, 4, t);
    bool success;

    display(g->b, "expecting: row 0-3 and col 0-1\n", g->b != NULL);

    success = drop_piece(g, 0);
    display(g->b, "expecting: black * in row 3, col 0, success = 1\n", success);

    success = drop_piece(g, 1);
    display(g->b, "expecting: white o in row 3, col 1, success = 1\n", success);

    success = drop_piece(g, 1);
    display(g->b, "expecting: black * in row 2, col 1, success = 1\n", success);

    success = drop_piece(g, 0);
    display(g->b, "expecting: white o in row 2, col 0, success = 1\n", success);

    success = drop_piece(g, 0);
    display(g->b, "expecting: black * in row 1, col 0, success = 1\n", success);

    success = drop_piece(g, 1);
    display(g->b, "expecting: white o in row 1, col 1, success = 1\n", success);

    success = drop_piece(g, 1);
    display(g->b, "expecting: black * in row 0, col 1, success = 1\n", success);

    success = drop_piece(g, 0);
    display(g->b, "expecting: white o in row 0, col 0, success = 1\n", success);

    test_game_outcome(g, "expecting DRAW: ");

    game_free(g);
}


/* game3: simulates game3 - includes invalid move, magnetize, and maglock = 0 */
void game3(enum type t) {
    printf("----- game3 -----\n");
    game* g = new_game(2, 0, 3, 3, t);
    bool success;

    success = drop_piece(g, 1);
    display(g->b, "expecting: black * in row 2, col 1, success = 1\n", success);

    success = drop_piece(g, 1);
    display(g->b, "expecting: white o in row 1, col 1, success = 1\n", success);

    success = drop_piece(g, 1);
    display(g->b, "expecting: black * in row 0, col 1, success = 1\n", success);

    success = drop_piece(g, 5);
    display(g->b, "expecting: no change, success = 0\n", success);

    success = magnetize(g);
    display(g->b, "expecting white magnetize:\nsuccess = 1\n"
            "...\n.*.\n.*o\n", success);

    success = drop_piece(g, 2);
    display(g->b, "expecting: black * in row 1, col 2, success = 1\n", success);

    success = drop_piece(g, 1);
    display(g->b, "expecting: white o in row 0, col 1, success = 1\n", success);

    success = drop_piece(g, 0);
    display(g->b, "expecting: black * in row 2, col 0, success = 1\n", success);

    success = drop_piece(g, 2);
    display(g->b, "expecting: white o in row 0, col 2, success = 1\n", success);

    success = magnetize(g);
    display(g->b, "expecting black magnetize:\nsuccess = 1\n"
            ".o.\n**o\n**o\n", success);

    test_game_outcome(g, "expecting BLACK WINS: ");

    game_free(g);
}


/* main: run the evidence functions above */
int main(int argc, char *argv[]) {
    game1(MATRIX);
    game1(BITS);

    game2(MATRIX);
    game2(BITS);

    game3(MATRIX);
    game3(BITS);

    test_board_get(MATRIX);
    test_board_get(BITS);

    test_board_set(MATRIX);
    test_board_set(BITS);

    test_board_new(MATRIX);
    test_board_new(BITS);

    test_magnetize(MATRIX);
    test_magnetize(BITS);

    test_drop_piece(MATRIX);
    test_drop_piece(BITS);

    test_new_game(MATRIX);
    test_new_game(BITS);

    test_header(MATRIX);
    test_header(BITS);

    test_swap_pos(MATRIX);
    test_swap_pos(BITS);

    test_make_pos();

    return 0;
}