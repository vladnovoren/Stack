#include "stack.h"

int main(){
    Stack test;
    test = Stack_Init();
    return 0;
    Push(&test, 1); 
    Pop(&test);
    Pop(&test);
    Push(&test, 2);
    printf("%d\n", Back(&test));
    Push(&test, 3);
    printf("%d\n", Back(&test));
    Push(&test, 4);
    printf("%d\n", Back(&test));
    return 0;
}