/* Recursive call using exec*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int height = 51;

//use execvp to run helloExec
int main(int argc, char const *argv[])
{
    printf("selfExec PID %d\n", getpid());
    printf("heigth:%d\n",height);
    height--;
    
    if (argc!=2) {
        printf("pass 1 argument as integer\n");
        exit(1);
    }
    
    int n = atoi(argv[1]);
    printf("%d...",n);

    if (n!=0) {
        char nMinus1[10];
        sprintf(nMinus1, "%d", n-1); // sends formatted output" " to a string pointed to, by str(nMinus1).
        printf("Arg to pass %s\n", nMinus1);
        execl(argv[0], argv[0], nMinus1, NULL);
    }

    printf("must not print this -- exec call does not return, error if it returns here\n");

    return 0; 
}
