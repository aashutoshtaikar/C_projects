#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef void (*func_ptr_t)(uint32_t);
static func_ptr_t cb_ptr = NULL;

int register_cb(func_ptr_t my_func)
{
     int r = -1;

     if (cb_ptr == NULL)
     {
          cb_ptr = my_func;
          r = 0;
     }
     //else - already in use! Fail!

     return r;
}

int run_cb(func_ptr_t my_func){
    int r = -1;

    if (cb_ptr!=NULL){
        cb_ptr(1);
        r = 0;
        cb_ptr=NULL;
    }
    else{
        printf("call back not registered cannot run\n");
    }
    return r;
}

void somefunc(){
    printf("running somefunc\n");
}

int main(){
    register_cb(somefunc); 
    run_cb(somefunc);
    run_cb(somefunc);
    return EXIT_SUCCESS;
}