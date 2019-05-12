#include<stdio.h>
#include<stdlib.h>
#include "Rectangle.h"

int main(){
    rectangle_t* x = new_rectangle();
    // x = new_rectangle("ash", 1, 2);
    x->set_length(x,1);
    x->set_breadth(x,2);
    print_rectangle(x);
    return 0;
}