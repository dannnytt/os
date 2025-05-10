#include <stdlib.h>
#include <string.h>

#include "list.h"


List* searchByLastname(List* list, const char *lastname) {

    Node *head = list->head;
    List *out = initList();

    while(head != NULL) {
        
        if (strcmp(head->person->lastname, lastname) == 0) {
            Person *copy = (Person*) malloc(sizeof(Person));
            memcpy(copy, head->person, sizeof(Person));
            addNode(out, copy);
        }
        head = head->next;
    }
    
    return out;
}

