#include <stdio.h>
#include "list.h"
#include "utils.h"

void search(List *list, List (*func_search())) {
    char field[256];
    scanf("%s", field);
    List *result = func_search(list, field);
    printf("\nРезультат поиска:\n");
    printList(result);
    clearList(result);                
    clickEsc();
}