#include <stdio.h>

#include "list.h"
#include "grade-map.h"


void printList(List* list) {
    
    Node *current = list->head;
    while(current != NULL) {
        printf("%d %s %s %s %s\n", 
                current->person->number, 
                current->person->lastname, 
                current->person->firstname, 
                current->person->patronymic,
                gradeToString(current->person->grade));
        
        current = current->next;
    }    
}
