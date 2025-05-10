#include <stdlib.h>
#include <string.h>

#include "list.h"

void addNode(List *list, Person *personInfo) {

    Node *newNode = (Node*) malloc(sizeof(Node));
    newNode->person = personInfo;

    newNode->next = NULL;
    newNode->prev = NULL;

    if (list->head == NULL) {
        list->head = newNode;
        list->tail = newNode;
    } else {
        newNode->prev = list->tail;
        list->tail->next = newNode;
        list->tail = newNode;
    }
}