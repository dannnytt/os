#include <stdio.h>
#include <stdlib.h>

#include "list.h"
#include "keyread.h"
#include "utils.h"

 
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
