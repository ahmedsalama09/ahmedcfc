#include "linked_list.h"

/*create the list by init the head to null*/
uint8_t create_list(list *pl){

    pl->head = NUL;
    pl->size = LOW;
}

/*insert the list members
par pl ... pointer to list , element... the element to be pushed, pos... the position to be inserted in*/
uint8_t insert_list(list *pl,list_datatype element,uint16_t pos){

    /*two temp members to create the node and to hold the position at where it'll be inserted at*/
    node *pn,*pq;
    uint16_t loop=LOW;

    pn = (node *) malloc(sizeof(node));

    /*check if it's taken*/
    if(pn){
    pn->element = element;

    /*if the first element is inserted then use head to point to it*/
    if(pos == LOW){
        pn->next = pl->head;
        pl->head = pn;
    }
  else{
        /*init the temp node to start from the first*/
        pq = pl->head;

        /*loop to reach the desired position and remember that you need to stop before it by 1 so you can reach it*/
        for(loop=0 ; loop<pos-1 ; loop++){

            pq = pq->next;
        }
        /*let pn node point to the next node to it and then the node before it point to it*/
        pn->next = pq->next;
        pq->next = pn;
        }
  pl->size++;
    }
}

/*delete any node at any position
@par: pl... pointer to list, element... the element you will get, pos... the position where you wanna delete from*/
uint8_t delete_list(list *pl,list_datatype *element,uint16_t pos){

    uint16_t loop = LOW;

    node *pn = NUL,*pq = NUL;

    if(pos == LOW){

        element = pl->head->element;
        pn = pl->head;
        pl->head = pl->head->next;
        free(pn->next);
    }
    else{
        pn = pl->head;

        for(loop = 0; loop < pos-1; loop++){
            pn = pn->next;
        }

        /*read the element and save the node at tmp memory to delete it by*/
        *element = pn->next->element;
        pq = pn->next;
        pn->next = pn->next->next;
        free(pq);
        pq = NUL;
    }
    pl->size--;
}

/*empty list checking @par p1... pointer to list, returns true or false*/
uint8_t empty_list(list *pl){

    /*return 0 if size not zero and 1 if it's as indication of empty stack*/
    if(pl->size)
        return LOW;

    else
        return LOW;
}

/*stack size function @par ... pointer to list, returns size of list*/
uint16_t list_size(list *pl){

    return pl->size;
}
