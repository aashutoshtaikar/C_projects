#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main(int argc, char const *argv[])
{
    pid_t pid = fork();
    if(pid<0){
        perror("fork failed");
        exit(1);
    }
    else if(pid==0)
    {
        //child now execs
        char* args[] = {"./bogosort","2","1","3","4",NULL};
        execvp(args[0], args);
    }
    
    //parent
    printf("Parent is now doing something\n");

    printf("Parent is waiting for child process\n");
    wait(NULL);
    

    return 0; 
}
