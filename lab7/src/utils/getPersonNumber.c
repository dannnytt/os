#include <stdlib.h>

#include "list.h"

int getPersonNumber(List *list) {
    return ((list == NULL || list->head == NULL) ? 1 : list->tail->person->number + 1);
}