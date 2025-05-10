#include <stdlib.h>

#include "list.h"

void clearList(List *list) {
    
    Node *current = list->head;
    while(current != NULL) {
        Node *tmp = current;
        current = current->next;
        free(tmp->person);
        free(tmp);
    }

    list->head = NULL;
}
