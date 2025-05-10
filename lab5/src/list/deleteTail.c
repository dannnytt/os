#include <stdlib.h>

#include "list.h"

void deleteTail(List *list) {

    if(list->tail == NULL) {
        return;
    }

    Node *tailElem = list->tail;

    if (list->head == list->tail) {
        list->head = NULL;
        list->tail = NULL;
    }

    list->tail = tailElem->prev;
    list->tail->next = NULL;
    free(tailElem);
}