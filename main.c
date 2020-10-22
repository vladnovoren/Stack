#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include "funcs_pub.h"

int main(){
    Stack *a;
    a = Init_Stack();
    for(int pos = 0; pos < 5; pos++)
        Push(a, 1);
    // //Dump_Stack(&a);
    // //Push(a, 2);
    // //Dump_Stack(&a);
    // //Push(a, 3);
    // //Dump_Stack(&a);
    // printf(PRINT_FLAG, Back(a));
    // printf("\n");
    // // Pop(a);
    // // Pop(a);
    // // Pop(a);
    // // Pop(a);
    // // Pop(a);
    // // Pop(a);
    // // Pop(a);
    // // Pop(a);

    // printf("%zu\n", Size(a));

    Destruct_Stack(a);

    return 0;
}