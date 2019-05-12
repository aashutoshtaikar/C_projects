#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct
{
    char* name;
    float length;
    float breadth;
    float area;

    //functions
    void(*set_length)(struct rectangle_t* rect,float l);
    void(*set_breadth)(struct rectangle_t* rect,float b);

}rectangle_t;

// typedef struct Rectangle rectangle_t;
rectangle_t* new_rectangle(void);
rectangle_t* new_rectangle_with(char* name,float l, float b);

void set_length(rectangle_t* rect,float l);
void set_breadth(rectangle_t* rect,float b);

void print_rectangle(rectangle_t* rect);

