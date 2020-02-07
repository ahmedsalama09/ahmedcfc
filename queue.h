#ifndef QUEUE_H_INCLUDED
#define QUEUE_H_INCLUDED

#include "data_types.h"
typedef uint32_t queue_datatype;

/*struct of queue takes front and last element*/
typedef struct queue{
uint16_t front;
uint16_t end;
uint16_t counter;
uint16_t size;
queue_datatype *q_data;
}queue;

/*first init Queue by passing address of it and it's size*/
uint8_t queue_init(queue *pq,uint16_t q_size);

/*push elements into queue*/
uint8_t in_queue(queue *pq,queue_datatype element);

/*read elements from queue*/
uint8_t de_queue(queue *pq,queue_datatype *p_element);

/*clear queue by reinit counter*/
void clear_queue(queue *pq);

/*check if queue is empty*/
uint8_t queue_empty(queue *pq);

/*check if queue is full*/
uint8_t queue_full(queue *pq);

/*function returns Q.Size*/
uint16_t queue_size(queue *pq);


#endif // QUEUE_H_INCLUDED
