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


List* initList();
void addNode(List *list, Person *personInfo);
void deleteHead(List *list);
void deleteTail(List *list);
void printList(List *list);

void clearList(List *list);
void serializeList(List *list, const char *filename);
void deserializeList(List *list, const char *filename);

List* searchByFirstname(List *list, const char *firstname);
List* searchByLastname(List *list, const char *lasttname);
List* searchByGrade(List *list, const char *grade);
void deleteById(List *list, unsigned int id);
