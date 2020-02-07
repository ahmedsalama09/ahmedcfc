#include <stdio.h>
#include "linked_list.h"
#include "stack.h"
#include "queue.h"

int main (void)
{
    int i,n=0;
    queue_datatype op1,op2,ope;
    queue q;
    queue_init(&q,40);
    char ar[] = "(75+90)";
    for(i=0;i<11;i++){
        if(ar[i] >=48 && ar[i] <= 57)
            n = n*10+(ar[i]-48);
        else if(ar[i] == '+' || ar[i] == '-' || ar[i] == '*' || ar[i] == '/' ){
            in_queue(&q,n);
            n=0;
            in_queue(&q,ar[i]);
        }
        else if (n !=0){
                in_queue(&q,n);
                n=0;
        }

    }

    de_queue(&q,&op1);

    while(!queue_empty(&q)){
        de_queue(&q,&ope);
        de_queue(&q,&op2);

        switch(ope){
        case '+':
            op1 = op2+op1;

            break;
        case '-':
            op1 = op1-op2;
            break;
        case '*':
            op1 = op1*op2;
            break;
        case '/':
            op1 = op1/op2;
            break;
        }
    }
    printf("%d",op1);
    return 0;
}

