
#include "stack.h"

/*create stack API: Takes pointer to stack and size of it
return : condition 1-->successful created, 0 -->failed to create*/
uint8_t create_stack(stack *ps,uint16_t size){

/*allocate stack at running time*/
ps->pdata = (stack_datatype *)malloc(sizeof(stack_datatype) * size);

/*check if it was taken or not*/
if(ps->pdata){

/*init the stack pointer and stack size*/
ps->top = 0;
ps->max_size = size;

return 1;
}

else
    return 0;
}

/*push elements to stack ps->pointer to stack, element the element to be pushed*/
uint8_t push_stack(stack *ps,stack_datatype element){

/*check for the size limits*/
if(ps->top <= ps->max_size){

/*push it*/
ps->pdata[ps->top]= element;
ps->top++;

return 1;
}

else
    return 0;
}

/*pop the element and put it in the reference of the Variable*/
uint8_t pop_stack(stack *ps,stack_datatype *element){

/*check if it's not empty*/
    if(ps->top >0){
            /*pop it and decrement the stack pointer*/
        ps->top--;
        *element = ps->pdata[ps->top];
        return 1;
    }

    else
        return 0;
}

/*check if the stack full or not */
uint8_t stack_full(stack *ps){

    if(ps->top == ps->max_size)
        return 1;

    else
        return 0;
}

/*check if the stack is empty or not*/
uint8_t stack_empty(stack *ps){

    if(ps->top == 0)
        return 1;

    else
        return 0;
}

/*clear the stack */
void clear_stack(stack *ps){

ps->top =0;
}

/*return the size of this stack at anytime*/
uint16_t stack_size(stack *ps){

return ps->top;}



/* if you want to view all elements without deleting any element*/
void viewonly_stack(stack *ps){

    int i=ps->top-1;

    for(;i>=0;i--){
        printf("%d ",ps->pdata[i]);
    }
}

/*check for the balanced Parenthesis inputs: pointer to stack,parenthesis array, size of the array*/
char *check_parenthesis(stack *ps,uint8_t *paren,uint16_t size){

    /*loop and temporary data holder*/
    uint8_t loop;
    uint8_t tmp_paren;

    for(loop=0;loop<size;loop++){

        /*if you found the start of any parenthesis then push it to stack*/
        if(paren[loop] == '(' || paren[loop] == '[' || paren[loop] == '{'){

            push_stack(ps,paren[loop]);
           }
        /*if you find the end of any parenthesis check it was last pushed one to find if balanced or not*/
        else{
            switch(paren[loop]){

            case ')':
                pop_stack(ps,&tmp_paren);

                if(tmp_paren == '[' || tmp_paren =='{')
                    return "NOT BALANCED";

                    break;

            case '}':
                pop_stack(ps,&tmp_paren);

                if(tmp_paren == '(' || tmp_paren == '[')
                    return "NOT BALANCED";

                    break;

            case ']':
                pop_stack(ps,&tmp_paren);

                if(tmp_paren == '(' || tmp_paren == '{')
                    return "NOT BALANCED";

                    break;
            }
        }
    }
    /*if nothing happened above then it's balanced*/
    if(stack_empty(ps))
        return "BALANCED";
    else
            return "NOT BALANCED";
}
