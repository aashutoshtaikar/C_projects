/*
 * stack.c
 *
 *  Created on: Feb 5, 2019
 *      Author: Aashutosh Taikar
 */
#include"Stack1.h"



struct Stack
{
    int count;
    block_header_t* header[];
};

Stack_t* createStack(int size)
{
	Stack_t* stack = (Stack_t*) malloc(sizeof(Stack_t));
	return stack;
}

void s_push(Stack_t* stack, block_header_t* header)
{
	stack->header[stack->count] = header;
	stack->count++;
}

void s_print(Stack_t* stack)
{
	for(int i = 0; i < stack->count; i++){
		printf("Stack header:%p \n", stack->header[i]);
	}
}


block_header_t* s_pop(Stack_t* stack)
{
    if (stack->count == 0) return 0;
    stack->count--;
    block_header_t* header = stack->header[stack->count];
    stack->header[stack->count] = NULL;
    return header;
}