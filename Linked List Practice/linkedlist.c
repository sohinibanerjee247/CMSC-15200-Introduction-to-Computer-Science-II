#include <stdlib.h>
#include <stdio.h>
#include "linkedlist.h"

intlist* add_beginning(intlist* l, int value)
{
    intlist* node = (intlist*)malloc(sizeof(intlist));
    node->value = value;
    node->next = l;
    return node;
}

intlist* add_end(intlist* l, int value)
{
    intlist* node = (intlist*)malloc(sizeof(intlist));
    node->value = value;
    node->next = NULL;

    if (l == NULL) {
        return node;
    }
    intlist* current = l;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = node;
    return l;
}

intlist* remove_first(intlist* l)
{
    if (l == NULL) {
        printf("remove_first error: empty list\n");
        return NULL;
    }
    intlist* delete = l;
    l = l->next;
    free(delete);
    return l;
}

intlist* remove_last(intlist* l)
{
    if (l == NULL) {
        printf("remove_last error: empty list\n");
        return NULL;
    }
    if (l->next == NULL) {
        free(l);
        return NULL;
    }

    intlist* current = l;
    while (current->next->next != NULL) {
        current = current->next;
    }
    free(current->next);
    current->next = NULL;
    return l;
}

intlist* insert_index(intlist* l, unsigned int index, int value)
{
    if (l == NULL) {
        printf("insert_index error: cannot insert index at empty list\n");
        return l;
    }
    int current_index = 0;
    intlist* current = l;
    while (current->next != NULL && current_index < index) {
        current = current->next;
        current_index++;
    }
    if (current_index == index) {
        intlist* insert = (intlist*)malloc(sizeof(intlist));
        insert->value = value;
        insert->next = current->next;
        current->next = insert;
        return l;
    } else {
        printf("insert_index error: insertion out of bounds\n");
        return l;
    }
}

intlist* remove_index(intlist* l, unsigned int index)
{
    if (l == NULL) {
        printf("remove_index error: cannot remove at empty list\n");
        return l;
    }
    if (index == 0) {
        return remove_first(l);
    }
    int current_index = 0;
    intlist* current = l;
    while (current->next != NULL && current->next->next != NULL && current_index < index - 1) {
        current = current->next;
        current_index++;
    }
    if (current->next != NULL && current_index == index - 1) {
        intlist* delete = current->next;
        current->next = current->next->next;
        free(delete);
        return l;
    } else {
        printf("remove_index error: removal out of bounds\n");
        return l;
    }
}

intlist* remove_value(intlist* l, int value)
{
    if (l == NULL) {
        printf("remove_value error: cannot remove at empty list\n");
        return l;
    }
    if (l->value == value) {
        return remove_first(l);
    }
    intlist* current = l;
    while (current->next != NULL && current->next->next != NULL && current->next->value != value) {
        current = current->next;
    }
    if (current->next != NULL && current->next->value == value) {
        intlist* delete = current->next;
        current->next = current->next->next;
        free(delete);
        return l;
    } else {
        printf("remove_value error: value not found\n");
        return l;
    }
}

intlist* merge(intlist* l1, intlist* l2)
{
    intlist* head = NULL;
    while (l1 != NULL || l2 != NULL) {
        if (l2 == NULL || (l1 != NULL && l1->value <= l2->value)) {
            head = add_end(head, l1->value);
            l1 = l1->next;
        } else {
            head = add_end(head, l2->value);
            l2 = l2->next;
        }
    }
    return head;
}