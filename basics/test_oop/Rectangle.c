#include "Rectangle.h"

// typedef struct Rectangle
// {
//     char* name;
//     float length;
//     float breadth;
// }rectangle_t;

rectangle_t* new_rectangle(void){
    return new_rectangle_with(NULL, 0, 0);
}

rectangle_t* new_rectangle_with(char* name,float l, float b){
    rectangle_t* rect = (rectangle_t*)malloc(sizeof(rectangle_t));
     rect->name = name;
     rect->length = l;
     rect->breadth = b;
     rect->area = l*b;
     rect->set_length = &set_length;
     rect->set_breadth = &set_breadth;
    return rect;
}

void set_length(rectangle_t* rect,float l){
    rect->length = l;
}

void set_breadth(rectangle_t* rect,float b){
    rect->breadth = b;
}



void print_rectangle(rectangle_t* rect){
    printf(" name:%s\n length:%f\n breadth:%f\n area:%f\n ", rect->name, rect->length, rect->breadth, rect->area);
}