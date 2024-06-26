#include <stdlib.h>
#include <stdio.h>
#include "linkedlist.h"

void free_linked_list(intlist* l)
{
    intlist* n;
    while (l != NULL) {
        n = l->next;
        free(l);
        l = n;
    }
}

void print_linked_list(intlist* l)
{
    while (l != NULL) {
        printf("%d ", l->value);
        l = l->next;
    }
    printf("\n\n");
}

void test_merge()
{
    printf("----- test_merge\n");
    intlist* l1 = NULL;
    l1 = add_end(l1, 1);
    l1 = add_end(l1, 2);
    l1 = add_end(l1, 3);
    l1 = add_end(l1, 3);
    l1 = add_end(l1, 5);
    l1 = add_end(l1, 7);

    intlist* l2 = NULL;
    l2 = add_end(l2, 2);
    l2 = add_end(l2, 3);
    l2 = add_end(l2, 4);
    l2 = add_end(l2, 4);
    l2 = add_end(l2, 6);

    intlist* res1 = merge(l1, l2);
    printf("1 2 2 3 3 3 4 4 5 6 7 (expecting)\n");
    print_linked_list(res1);
    free_linked_list(l1);
    free_linked_list(l2);
    free_linked_list(res1);

    intlist* l3 = NULL;
    intlist* l4 = NULL;
    l3 = add_end(l3, 5);

    intlist* res2 = merge(l3, l4);
    printf("5 (expecting)\n");
    print_linked_list(res2);
    free_linked_list(l3);
    free_linked_list(l4);
    free(res2);
}

void print_key()
{
    printf("a: add_beginning - value\n");
    printf("b: add_end - value\n");
    printf("c: remove_first\n");
    printf("d: remove_last\n");
    printf("e: insert_index - index, value\n");
    printf("f: remove_index - index\n");
    printf("g: remove_value - value\n");
    printf("\n");
}

void play_interactive()
{
    char command = '\0';
    int index, value;
    intlist* l = NULL;
    print_key();
    while (command != 'q') {
        scanf(" %c", &command);
        switch (command) {
            case 'a':
                scanf(" %d", &value);
                l = add_beginning(l, value);
                break;
            case 'b':
                scanf(" %d", &value);
                l = add_end(l, value);
                break;
            case 'c':
                l = remove_first(l);
                break;
            case 'd':
                l = remove_last(l);
                break;
            case 'e':
                scanf(" %d", &index);
                scanf(" %d", &value);
                l = insert_index(l, index, value);
                break;
            case 'f':
                scanf(" %d", &index);
                l = remove_index(l, index);
                break;
            case 'g':
                scanf(" %d", &value);
                l = remove_value(l, value);
                break;
        }
        printf("Linked List: ");
        print_linked_list(l);
    }
    printf("Final Linked List: ");
    print_linked_list(l);
    free_linked_list(l);
}

/* main: run the evidence functions above */
int main(int argc, char *argv[])
{
    //test_merge();
    play_interactive();

    return 0;
}