#include <stdio.h>

#include "grade-convert.h"
#include "person.h"

void inputPersonInfo(Person *info) {

    printf("Фамилия: "); 
    scanf("%s", info->lastname);
    
    printf("Имя: "); 
    scanf("%s", info->firstname);
    
    printf("Отчество: "); 
    scanf("%s", info->patronymic);
    
    printf("Оценка: ");
    char buf[256]; 
    scanf("%s", buf);
    info->grade = STR_TO_GRADE(buf);
}