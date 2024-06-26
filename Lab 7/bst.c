#include <stdlib.h>
#include <stdio.h>
#include "adrbook.h"

const char *_bst_todo_format = "TODO [bst]: %s\nhalting\n";


bst *bst_singleton(vcard *c) {
    bst* res = (bst*)malloc(sizeof(bst));
    if (res == NULL) {
        fprintf(stderr, "bst_singleton error: memory not allocated");
    }
    res->c = c;
    res->left = NULL;
    res->right = NULL;
    return res;
}


int bst_insert(bst *t, vcard *c) {
    if (t == NULL) {
        fprintf(stderr, "bst_insert error - cannot insert to empty tree\n");
        exit(1);
    }

    int cmp_ans = strcmp(c->cnet, t->c->cnet);
    if (cmp_ans < 0) {
        if (t->left != NULL) {
            return bst_insert(t->left, c);
        } else {
            t->left = bst_singleton(c);
            return 1;
        }
    } else if (cmp_ans > 0) {
        if (t->right != NULL) {
            return bst_insert(t->right, c);
        } else {
            t->right = bst_singleton(c);
            return 1;
        }
    } else {
        return 0;
    }
}


unsigned int bst_num_entries(bst *t) {
    if (t == NULL) {
        return 0;
    }
    return 1 + bst_num_entries(t->left) + bst_num_entries(t->right);
}


/* maximum: returns max of 2 unsigned ints */
unsigned int maximum(unsigned int a, unsigned int b) {
    if (a >= b) {
        return a;
    }
    return b;
}


unsigned int bst_height(bst *t) {
    if (t == NULL) {
        return 0;
    }
    return 1 + maximum(bst_height(t->left), bst_height(t->right));
}


vcard *bst_search(bst *t, char *cnet, int *n_comparisons) {
    if (t == NULL) {
        return NULL;
    }
    (*n_comparisons)++;

    int cmp_ans = strcmp(cnet, t->c->cnet);
    if (cmp_ans < 0) {
        return bst_search(t->left, cnet, n_comparisons);
    } else if (cmp_ans > 0) {
        return bst_search(t->right, cnet, n_comparisons);
    } else {
        return t->c;
    }
}


/* note: f is the destination of the output, e.g. the screen;
 * our code calls this with stdout, which is where printfs are sent;
 * simply use fprintf rather than printf in this function, and pass in f
 * as its first parameter
 */
unsigned int bst_c(FILE *f, bst *t, char c) {
    if (t == NULL) {
        return 0;
    }

    unsigned int add = 0;
    if (c <= t->c->cnet[0]) {
        add += bst_c(f, t->left, c);
    }
    if (t->c->cnet[0] == c) {
        fprintf(f, "%s\n", t->c->cnet);
        add++;
    }
    if (c >= t->c->cnet[0]) {
        add += bst_c(f, t->right, c);
    }

    return add;
}


void bst_free(bst *t) {
    if (t == NULL) {
        return;
    }
    bst_free(t->left);
    bst_free(t->right);
    vcard_free(t->c);
    free(t);
}
