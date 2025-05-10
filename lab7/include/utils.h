#include "list.h"

void instruction();
void clickEsc();
void search(List *list, List* (*func_search) (List*, const char*));
void inputPersonInfo(Person *info);
int getPersonNumber(List *list);