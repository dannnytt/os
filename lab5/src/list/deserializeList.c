#include <stdio.h>
#include <stdlib.h>

#include "list.h"

void deserializeList(List *list, const char *filename) {
    
    FILE *file = fopen(filename, "r");
    
    clearList(list);

    Person info;
    while (fread(&info, sizeof(Person), 1, file) == 1)  {
        
        Person *newPerson = (Person*) malloc(sizeof(Person));
        *newPerson = info;
        addNode(list, newPerson);    
    }
    fclose(file);
}