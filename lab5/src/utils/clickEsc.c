#include <stdio.h>

#include "keyread.h"

void clickEsc() {
    printf("Вернуться обратно ESC\n");
    while (getch() != EXIT) {}
}