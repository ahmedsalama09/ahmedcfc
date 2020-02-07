#ifndef LINKED_LIST_H_INCLUDED
#define LINKED_LIST_H_INCLUDED
#include "data_types.h"


typedef int list_datatype;

typedef struct node{

    list_datatype element;
    struct node *next;
}node;

typedef struct list{

    node *head;
    uint16_t size;
}list;


/*create the list by init the head to null*/
uint8_t create_list(list *pl);

/*insert the list members
par pl ... pointer to list , element... the element to be pushed, pos... the position to be inserted in*/
uint8_t insert_list(list *pl,list_datatype element,uint16_t pos);

/*delete any node at any position
@par: pl... pointer to list, element... the element you will get, pos... the position where you wanna delete from*/
uint8_t delete_list(list *pl,list_datatype *element,uint16_t pos);

/*empty list checking @par p1... pointer to list, returns true or false*/
uint8_t empty_list(list *pl);

/*stack size function @par ... pointer to list, returns size of list*/
uint16_t list_size(list *pl);
#endif // LINKED_LIST_H_INCLUDED
