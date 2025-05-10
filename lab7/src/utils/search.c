#include <stdio.h>
#include "list.h"
#include "utils.h"

#include "functions-pointers.h"

void search(List *list, List* (*func_search) (List*, const char*)) {
    char field[256];
    scanf("%s", field);
    List *result = func_search(list, field);
    printf("\nРезультат поиска:\n");
    funcs_ptrs.print_list(result);
    funcs_ptrs.clear_list(result);                
    clickEsc();
}