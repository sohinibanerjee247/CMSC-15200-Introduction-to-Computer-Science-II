#ifndef POS_H
#define POS_H

/* pos: struct with row and column */
struct pos {
    unsigned int r, c;
};

typedef struct pos pos;


/* make_pos: create pos struct from row and column */
pos make_pos(unsigned int r, unsigned int c);

#endif /* POS_H */