#include <stdio.h>
#include <stdlib.h>

#include "list.h"
#include "keyread.h"
#include "grade-map.h"
#include "utils.h"

int getPersonNumber(List *list) {
    return ((list == NULL || list->head == NULL) ? 1 : list->tail->person->number + 1);
}

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
    info->grade = stringToGrade(buf);
}

void search(List *list, List (*func_search())) {
    char field[256];
    scanf("%s", field);
    List *result = func_search(list, field);
    printf("\nРезультат поиска:\n");
    printList(result);
    clearList(result);                
    clickEsc();
}

int main(int argc, char **argv) {
    
    List *list = initList();
    Person *info; 
    
    const char filename[] = {"journal.bin"};             
    char ch;
    while(ch != EXIT) {
        system("clear");
        instruction();    
        ch = getch();
        
        switch(ch) {
        
            case PRINT_LIST :
                system("clear");
                printList(list);
                clickEsc();
                break;
            
            case ADD_NODE:
                system("clear");
                info = (Person*) malloc(sizeof(Person));
                info->number = getPersonNumber(list);
                inputPersonInfo(info);
                addNode(list, info);
                clickEsc();
                break;

            case DELETE_NODE:
                system("clear");
                printf("Введите удаляемый номер записи:\n");
                unsigned int id;
                scanf("%d", &id);
                deleteById(list, id);
                clickEsc();
                break;

            case SERIALIZE_LIST:
                system("clear");
                serializeList(list, filename);
                printf("Список сериализован.\n");
                clickEsc();
                break;

            case DESERIALIZE_LIST:
                system("clear");
                deserializeList(list, "journal.bin");
                printf("Список десериализован.\n");
                clickEsc();
                break;

            case SEARCH_BY_FIRSTNAME:
                system("clear");
                printf("Введите искомое имя:\n");
                search(list, searchByFirstname);
                break;
            
            case SEARCH_BY_LASTNAME:
                system("clear");
                printf("Введите искомую фамилию:\n");
                search(list, searchByLastname);
                break;

            case SEARCH_BY_GRADE: 
                system("clear");
                printf("Введите искомую оценку:\n");
                search(list, searchByGrade);
                break;
            
            case CLEAR_LIST:
                system("clear");
                clearList(list);
                printf("Список очищен\n");
                clickEsc();
                break;
        }
    }
   
    clearList(list);
    return 0;
}
