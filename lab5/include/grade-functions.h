#pragma once

#include <stdlib.h>
#include <string.h>

#define GRADE_TO_STR(grade) \
        ((grade == EXCELENT) ? "Отлично" : \
        (grade == GOOD) ? "Хорошо" : \
        (grade == SATISFACTORY) ? "Удовлетворительно" : \
        (grade == UNSATISFACTORY) ? "Неудовлетворительно" : \
        (grade == NONE) ? "Ничего" : "Неизвестно")
        
#define STR_TO_GRADE(str) \
        (strcmp(str, "Отлично") == 0 ? EXCELENT : \
        strcmp(str, "Хорошо") == 0 ? GOOD : \
        strcmp(str, "Удовлетворительно") == 0 ? SATISFACTORY : \
        strcmp(str, "Неудовлетворительно") == 0 ? UNSATISFACTORY : \
        strcmp(str, "Ничего") == 0 ? NONE : -1)

