#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "pos.h"
#include "board.h"
#include "logic.h"


/* get_header_item: finds character based on row/col position */
char get_header_item(unsigned int num) {
    unsigned int num_of_digits = 10;
    unsigned int num_of_letters = 'Z' - 'A' + 1;

    if (num < num_of_digits) {
        return num + '0';
    } else if (num < num_of_digits + num_of_letters) {
        return num + 'A' - num_of_digits;
    } else if (num < num_of_digits + 2 * num_of_letters) {
        return num + 'a' - num_of_digits - num_of_letters;
    } else {
        return '?';
    }
}


/* print_piece: prints char (*, o, .) based on cell color */
void print_piece(cell color) {
    switch (color) {
        case BLACK:
            printf("*");
            break;
        case WHITE:
            printf("o");
            break;
        case EMPTY:
            printf(".");
    }
}


board* board_new(unsigned int width, unsigned int height, enum type type) {
    board* b = (board*)malloc(sizeof(board));
    if (b == NULL) {
        fprintf(stderr, "board_new error - board not allocated\n");
        exit(1);
    }

    if (width == 0 || height == 0) {
        fprintf(stderr, "board_new error - 0 dim board not allowed\n");
        exit(1);
    }

    b->width = width;
    b->height = height;
    b->type = type;

    unsigned int max_per_line, total, area;
    switch (b->type) {
        case MATRIX:
            b->u.matrix = (cell**)malloc(height * sizeof(cell*));
            if (b->u.matrix == NULL) {
                fprintf(stderr, "board_new error - matrix not allocated\n");
                exit(1);
            }

            for (unsigned int r = 0; r < height; r++) {
                b->u.matrix[r] = (cell*)malloc(width * sizeof(cell));
                if (b->u.matrix[r] == NULL) {
                    fprintf(stderr, "board_new error - "
                            "row %c in matrix not allocated\n",
                            get_header_item(r));
                    exit(1);
                }
            }
            for (unsigned int r = 0; r < b->height; r++) {
                for (unsigned int c = 0; c < b->width; c++) {
                    pos p = make_pos(r, c);
                    board_set(b, p, EMPTY);
                }
            }
            break;
        case BITS:
            max_per_line = 16;
            area = b->height * b->width;
            total = area / max_per_line + (area % max_per_line != 0);
            b->u.bits = (unsigned int*)malloc(total * sizeof(unsigned int));
            if (b->u.bits == NULL) {
                fprintf(stderr, "board_new error - bits not allocated\n");
                exit(1);
            }
            for (unsigned int i = 0; i < total; i++) {
                b->u.bits[i] = 0;
            }
    }
    return b;
}


void board_free(board* b) {
    switch (b->type) {
        case MATRIX:
            for (unsigned int r = 0; r < b->height; r++) {
                free(b->u.matrix[r]);
            }
            free(b->u.matrix);
            break;
        case BITS:
            free(b->u.bits);
    }
    free(b);
}


void board_show(board* b) {
    printf("  ");
    for (unsigned int c = 0; c < b->width; c++) {
        printf("%c", get_header_item(c));
    }
    printf("\n  ");
    for (unsigned int c = 0; c < b->width; c++) {
        printf("-");
    }
    printf("\n");

    for (unsigned int r = 0; r < b->height; r++) {
        printf("%c|", get_header_item(r));
        for (unsigned int c = 0; c < b->width; c++) {
            print_piece(board_get(b, make_pos(r, c)));
        }
        printf("\n");
    }
    printf("\n");
}


cell board_get(board* b, pos p) {
    if (p.r >= b->height) {
        fprintf(stderr, "board_get error - row out of bounds\n");
        exit(1);
    }
    if (p.c >= b->width) {
        fprintf(stderr, "board_get error - column out of bounds\n");
        exit(1);
    }

    unsigned int max_per_line, current, bits_r, bits_c, full_value, shift;
    switch (b->type) {
        case MATRIX:
            return b->u.matrix[p.r][p.c];
        case BITS:
            max_per_line = 16;
            current = p.r * b->width + p.c;
            bits_r = current / max_per_line;
            bits_c = current % max_per_line;
            full_value = b->u.bits[bits_r];
            shift = 2 * bits_c;
            return (full_value >> shift) & 0x3;
    }
}


void board_set(board* b, pos p, cell c) {
    if (p.r >= b->height) {
        fprintf(stderr, "board_set error - row out of bounds\n");
        exit(1);
    }
    if (p.c >= b->width) {
        fprintf(stderr, "board_set error - column out of bounds\n");
        exit(1);
    }

    unsigned int max_per_line, current, bits_r, bits_c, full_value,
             shift, bit_mask, change;
    switch (b->type) {
        case MATRIX:
            b->u.matrix[p.r][p.c] = c;
            return;
        case BITS:
            max_per_line = 16;
            current = p.r * b->width + p.c;
            bits_r = current / max_per_line;
            bits_c = current % max_per_line;
            full_value = b->u.bits[bits_r];
            shift = 2 * bits_c;
            bit_mask = (0x3 << shift);
            change = (c << shift);
            b->u.bits[bits_r] = change | (full_value & ~bit_mask);
    }
}