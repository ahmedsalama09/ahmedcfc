#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED
#include <stdlib.h>
#include "data_types.h"

typedef char stack_datatype;

/*stack struct*/
typedef struct stack{
int top;
int max_size;
stack_datatype *pdata;
}stack;

/*create stack API: Takes pointer to stack and size of it
return : condition 1-->successful created, 0 -->failed to create*/
uint8_t create_stack(stack *ps,uint16_t size);

/*push elements to stack ps->pointer to stack, element the element to be pushed*/
uint8_t push_stack(stack *ps,stack_datatype element);

/*pop the element and put it in the reference of the Variable*/
uint8_t pop_stack(stack *ps,stack_datatype *element);

/*check if the stack full or not */
uint8_t stack_full(stack *ps);

/*check if the stack is empty or not*/
uint8_t stack_empty(stack *ps);

/*clear the stack */
void clear_stack(stack *ps);

/*return the size of this stack at anytime*/
uint16_t stack_size(stack *ps);

/* if you want to view all elements without deleting any element*/
void viewonly_stack(stack *ps);

/*check for the balanced Parenthesis inputs: pointer to stack,parenthesis array, size of the array*/
char *check_parenthesis(stack *ps,uint8_t *paren,uint16_t size);
#endif // STACK_H_INCLUDED
