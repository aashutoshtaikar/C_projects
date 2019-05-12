#include<stdio.h>
#include<stdlib.h>
#include "Rectangle.h"

int main(){
    rectangle_t* x = new_rectangle();
    x = new_rectangle_with("ash", 1, 2);
    x->add_length(x,1);
    print_rectangle(x);
    destroy(x);

    return 0;
}