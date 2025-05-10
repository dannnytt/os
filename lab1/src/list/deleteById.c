#include <stdlib.h>

#include "list.h"

void deleteById(List *list, unsigned int id) {
    
    // Если список пустой
    if (list == NULL || list->head == NULL) {
        return;  
    }

    Node *current = list->head;
    while (current != NULL && current->person->number != id) {
        current = current->next;
    }

    if (current == NULL) {
        return;  
    }

    if (current->prev != NULL) {
        current->prev->next = current->next;  
    } else {
        list->head = current->next;  
    }

    if (current->next != NULL) {
        current->next->prev = current->prev;  
    }

    // Освобождаем память
    free(current->person);  
    free(current);

    // Переиндексация номеров
    current = list->head;
    unsigned int i = 1;
    while (current != NULL) {
        current->person->number = i++;
        current = current->next;
    }
    
}