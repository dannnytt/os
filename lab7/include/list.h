#pragma once

#include "person.h"

typedef struct Node Node;
typedef struct List List;


struct Node {
    Node *next;
    Node *prev;
    Person *person;
};


struct List {
    Node *head;
    Node *tail;
};
