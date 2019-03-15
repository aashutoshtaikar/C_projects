#include <stdio.h>
#include <unistd.h>

//program to display arguments passed
int main(int argc, char* argv[]) {

    printf("helloExec PID %d\n",getpid());

    printf("helloExec arguments: ");
    for(int i = 0; i < argc; i++){
        printf("%s, ", argv[i]);
    }
    printf("\n");
    return 0;
}