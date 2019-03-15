#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int favNum = 84;

//use execvp to run helloExec
int main(int argc, char const *argv[])
{
    printf("execDemo PID %d\n", getpid());

  /* man exec
    with L:comman seperated arguments 
    with V:Vector (i.e. an array of strings)
    with P: include normal search path for executable 
  */
    char* args[] = {"./helloExec", "hello", "world", NULL};
    execv(args[0],args);
    // execvp(args[0], args); //execvp("path", args)   //with v & p(automatic serach path)   
    // execl(args[0],"hello","world"); //with L cannot programtically have array of strings like with V
    
    printf("must not print this -- exec call does not return, error if it returns here\n");

    return 0; 
}
