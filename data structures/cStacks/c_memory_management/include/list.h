/* list.h
    class to test memory management
 */
#include <stdio.h>  //io
#include <stdlib.h> //malloc
#include <stdbool.h>  //bool
#include <stdint.h> //int types

struct list; 

/* functions */
//add to list
void add(int data);

//delete from list
void del(int data);


//display entire list
void displ(list list_name);

