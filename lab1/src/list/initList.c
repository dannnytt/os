#include <stdlib.h>


#include "list.h"

List* initList() {
    
    List *tmp = (List*) malloc(sizeof(List));
    tmp->head = NULL;
    tmp ->tail = NULL;
    
    return tmp;
}