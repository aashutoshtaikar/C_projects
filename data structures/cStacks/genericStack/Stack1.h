#include <stdlib.h>
#include <stdbool.h>   // NOTE: c99 bool requires #include <stdbool.h>

typedef struct Stack Stack_t;

Stack_t* createStack(int size);

void s_push(Stack_t* stack, block_header_t* header);

void s_print(Stack_t* stack);

block_header_t* s_pop(Stack_t* stack);