#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>

#include "list.h"
#include "keyread.h"
#include "utils.h"
#include "functions-pointers.h"

funcs_pointers funcs_ptrs;

int main(int argc, char **argv) {
    
    void *handle = dlopen("libs/liblist.so", RTLD_LAZY);
    if (!handle) {
        fputs (dlerror(), stderr);
        exit(1);
    }
    
    funcs_pointers funcs_ptrs;
    
    funcs_ptrs.init_list = dlsym(handle, "initList");
    funcs_ptrs.add_node = dlsym(handle, "addNode");
    funcs_ptrs.delete_head = dlsym(handle, "deleteHead");    
    funcs_ptrs.delete_tail = dlsym(handle, "deleteTail");
    funcs_ptrs.print_list = dlsym(handle, "printList");
    funcs_ptrs.clear_list = dlsym(handle, "clearList");
    funcs_ptrs.serialize_list = dlsym(handle, "serializeList");
    funcs_ptrs.deserialize_list = dlsym(handle, "deserializeList");
    funcs_ptrs.search_by_firstname = dlsym(handle, "searchByFirstname");
    funcs_ptrs.search_by_lastname = dlsym(handle, "searchByLastname");
    funcs_ptrs.search_by_grade = dlsym(handle, "searchByGrade");    
    funcs_ptrs.delete_by_id = dlsym(handle, "deleteById");

    List *list = funcs_ptrs.init_list();
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
                funcs_ptrs.print_list(list);
                clickEsc();
                break;
            
            case ADD_NODE:
                system("clear");
                info = (Person*) malloc(sizeof(Person));
                info->number = getPersonNumber(list);
                inputPersonInfo(info);
                funcs_ptrs.add_node(list, info);
                clickEsc();
                break;

            case DELETE_NODE:
                system("clear");
                printf("Введите удаляемый номер записи:\n");
                unsigned int id;
                scanf("%d", &id);
                funcs_ptrs.delete_by_id(list, id);
                clickEsc();
                break;

            case SERIALIZE_LIST:
                system("clear");
                funcs_ptrs.serialize_list(list, filename);
                printf("Список сериализован.\n");
                clickEsc();
                break;

            case DESERIALIZE_LIST:
                system("clear");
                funcs_ptrs.deserialize_list(list, filename);
                printf("Список десериализован.\n");
                clickEsc();
                break;

            case SEARCH_BY_FIRSTNAME:
                system("clear");
                printf("Введите искомое имя:\n");
                search(list, funcs_ptrs.search_by_firstname);
                break;
            
            case SEARCH_BY_LASTNAME:
                system("clear");
                printf("Введите искомую фамилию:\n");
                search(list, funcs_ptrs.search_by_lastname);
                break;

            case SEARCH_BY_GRADE: 
                system("clear");
                printf("Введите искомую оценку:\n");
                search(list, funcs_ptrs.search_by_grade);
                break;
            
            case CLEAR_LIST:
                system("clear");
                funcs_ptrs.clear_list(list);
                printf("Список очищен\n");
                clickEsc();
                break;
        }
    }
   
    funcs_ptrs.clear_list(list);
    dlclose(handle);
    return 0;
}
