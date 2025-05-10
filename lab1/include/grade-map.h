#pragma once

#include "grades.h"

typedef struct GradeMap GradeMap;

struct GradeMap {
    Grade grade;
    const char* name;
};

const char* gradeToString(Grade grade);
Grade stringToGrade(const char* name);