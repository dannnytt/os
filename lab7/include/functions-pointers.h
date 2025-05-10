#pragma once
#include "list.h"

typedef struct funcs_pointers funcs_pointers;

struct funcs_pointers {
    List* (*init_list) (void);
    void (*add_node) (List*, Person*);
    void (*delete_head) (List*);
    void (*delete_tail) (List*);
    void (*print_list) (List*);
    void (*clear_list) (List*);
    void (*serialize_list) (List*, const char*);
    void (*deserialize_list) (List*, const char*);
    List* (*search_by_firstname) (List*, const char*);
    List* (*search_by_lastname) (List*, const char*);
    List* (*search_by_grade) (List*, const char*);
    void (*delete_by_id) (List*, unsigned int);
};

extern funcs_pointers funcs_ptrs;