#include "grade-map.h"

const char* gradeToString(Grade grade) {

    GradeMap map[] = {
        {NONE, "Ничего"},
        {UNSATISFACTORY, "Неудовлетворительно"},
        {SATISFACTORY, "Удовлетворительно"},
        {GOOD, "Хорошо"},
        {EXCELENT, "Отлично"},
    };


    const char *gradeName;
    for (int i = 0; i < (sizeof(map)) / (sizeof(map[0])); i++) {
        if (map[i].grade == grade) {
            gradeName = map[i].name;
        }
    }
    
    return gradeName;
}