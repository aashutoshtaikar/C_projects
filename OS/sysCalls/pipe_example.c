#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>

int main(int argc, char const *argv[])
{
    pid_t pid;
    int mypipefd[2],ret;
    char buf[20] = {'\0'};

    ret = pipe(mypipefd);
    if(ret==-1){
        perror("pipe");
        exit(1);
    }

    pid = fork();
    if (pid==0) {
        /* Child process */
        char* x = "Hello there!";
        write(mypipefd[1], x, strlen(x)); //1 is for writing
    }
    else{
        /* parent process */
        read(mypipefd[0],buf,15);
        printf("buf: %s\n", buf);
    }
    


    return 0;
}
