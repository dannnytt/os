#pragma once
#include "grades.h"

typedef struct Person Person;

struct Person{
    int number;
    char lastname[256];
    char firstname[256];
    char patronymic[256];
    Grade grade;
};
