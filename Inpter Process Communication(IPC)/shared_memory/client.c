/* IPC - shared mem example */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>

#define SHSIZE 100

int main(int argc, char const *argv[])
{
    int shmid;
    key_t key;
    char* shm;
    char* s;

    key = 9876;

    //get address from shmid
    shmid = shmget(key, SHSIZE, 0666);
    if (shmid<0) {
        perror("shmget error");
        exit(1);
    }

    //get pointer to the shared mem by attaching shmid to the shared mem
    shm = shmat(shmid,NULL,0);
    if (shm==(char*) -1) {
        perror("shmat error");
        exit(1);
    }
    
    //read from shared memory
    for( s=shm; *s !=0; s++){
        printf("%c",*s);
    }
    printf("\n");
    *shm = '*'; //change the first char in the first mem to * -- server will exit

    return 0;
}
