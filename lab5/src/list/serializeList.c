#include <stdio.h>

#include "list.h"

void serializeList(List *list, const char *filename) {
    
    FILE *file = fopen(filename, "wb");

    if (file == NULL) {
        perror("Ошибка открытия файла");
        return;
    }

    Node *current = list->head;

    while (current != NULL) {
        fwrite(current->person,sizeof(Person), 1, file);
        current = current->next;
    }
    fclose(file);
}