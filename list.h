#ifndef LIST_H_   
#define LIST_H_

struct List {
    int position;
    int *pointer;
};

void INITIALIZE_list (int length, struct List *list) ;

void ADD_list (int item, struct List *list) ;

void PRINT_list (struct List *list) ;

int CHECK_list (int item, struct List *list) ;

long RANDOM(struct List *list) ;

#endif // LIST_H_