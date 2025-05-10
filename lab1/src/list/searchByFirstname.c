#include <stdlib.h>
#include <string.h>

#include "list.h"


List* searchByFirstname(List* list, const char *firstname) {

    Node *head = list->head;
    List *out = initList();


    while(head != NULL) {
        
        if (strcmp(head->person->firstname, firstname) == 0) {
            Person *copy = (Person*) malloc(sizeof(Person));
            memcpy(copy, head->person, sizeof(Person));
            addNode(out, copy);
        }
        head = head->next;
    }
    
    return out;
}