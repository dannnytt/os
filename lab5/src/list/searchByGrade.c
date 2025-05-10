#include <stdlib.h>
#include <string.h>

#include "list.h"
#include "grade-functions.h"


List* searchByGrade(List* list, const char *grade) {
    
    Node *head = list->head;
    List *out = initList();

    while(head != NULL) {
        
        if (strcmp(GRADE_TO_STR(head->person->grade), grade) == 0) {
            Person *copy = (Person*) malloc(sizeof(Person));
            memcpy(copy, head->person, sizeof(Person));
            addNode(out, copy);
        }
        head = head->next;
    }

    return out;
}