#include <stdlib.h>

#include "list.h"

void deleteHead(List *list) {
    
    if(list->head == NULL) {
        return;
    }
    
    Node *headElem = list->head;

    if (list->head == list->tail) {
        list->head = NULL;
        list->tail = NULL;
    } 

    list->head = headElem->next;
    list->head->prev = NULL;
    free(headElem);
}


