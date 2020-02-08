#include "queue.h"

/*first init Queue by passing address of it and it's size*/
uint8_t queue_init(queue *pq,uint16_t q_size){

    /*create queue dynamically*/
    pq->q_data = (queue_datatype *) malloc(sizeof(queue_datatype) * q_size);

    if(pq){
    /*init top and end*/
    pq->counter=LOW;
    pq->end=LOW;
    pq->front=LOW;
    pq->size = q_size;

    return HIGH;
    }
    else
        return LOW;
}

/*push elements into queue*/
uint8_t in_queue(queue *pq,queue_datatype element){

    pq->end = pq->end % pq->size;

    /*check if there's some free area return 1 if you pushed successfully*/
    if(pq->counter < pq->size){

    /*send element to end*/
    pq->q_data[pq->end] = element;
    pq->end++;
    pq->counter++;

    return HIGH;
    }
    else
        return LOW;
}

/*read elements from queue*/
uint8_t de_queue(queue *pq,queue_datatype *p_element){

    pq->front = pq->front % pq->size;

    /*check if the queue isn't empty*/
    if(pq->counter > LOW){

        /*read front data and increment front*/
        *p_element = pq->q_data[pq->front];
        pq->front++;
        pq->counter--;
        return HIGH;
    }
    else
        return LOW;
}

/*check if queue is full*/
uint8_t queue_full(queue *pq){

    return (pq->counter == pq->size);
}

/*check if queue is empty*/
uint8_t queue_empty(queue *pq){

return (pq->counter == LOW);
}

/*clear queue by reinit counter*/
void clear_queue(queue *pq){

    /*write 0 to counter*/
    pq->counter = LOW;
}

/*function returns Q.Size*/
uint16_t queue_size(queue *pq){
return pq->counter;}

