typedef struct intlist intlist;

struct intlist {
    int value;
    intlist* next;
};

intlist* add_beginning(intlist* l, int value);

intlist* add_end(intlist* l, int value);

intlist* remove_first(intlist* l);

intlist* remove_last(intlist* l);

intlist* insert_index(intlist* l, unsigned int index, int value);

intlist* remove_index(intlist* l, unsigned int index);

intlist* remove_value(intlist* l, int value);

intlist* merge(intlist* l1, intlist* l2);