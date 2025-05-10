#include <string.h>
#include "grade-map.h"

Grade stringToGrade(const char *name) {

    GradeMap map[] = {
        {NONE, "Ничего"},
        {UNSATISFACTORY, "Неудовлетворительно"},
        {SATISFACTORY, "Удовлетворительно"},
        {GOOD, "Хорошо"},
        {EXCELENT, "Отлично"},
    };


    Grade grade;
    for (int i = 0; i < (sizeof(map)) / (sizeof(map[0])); i++) {
        if (strcmp(map[i].name, name) == 0) {
            grade = map[i].grade;
        }
    }
    
    return grade;
}