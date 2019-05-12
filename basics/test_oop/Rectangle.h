#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct Rectangle
{
    char* name;
    float length;
    float breadth;
    float area;

    void(*add_length)(struct Rectangle* rect,float l);
}rectangle_t;

// typedef struct Rectangle rectangle_t;
rectangle_t* new_rectangle(void);
rectangle_t* new_rectangle_with(char* name,float l, float b);
void destroy(rectangle_t* rect);

void add_length(rectangle_t* rect, float l);

void print_rectangle(rectangle_t* rect);

