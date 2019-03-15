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

    //create a shared memory
    shmid = shmget(key, SHSIZE, IPC_CREAT | 0666);
    if (shmid<0) {
        perror("shmget error");
        exit(1);
    }

    //attach and get the pointer to the memory
    shm = shmat(shmid,NULL,0);
    if (shm==(char*) -1) {
        perror("shmat error");
        exit(1);
    }
    
    //write to shared memory
    memcpy(shm, "Hello world", 11);

    s = shm;
    s += 11; //get pointer to end
    *s = 0; //null the end of the string

    //if the first char in the memory is * it will exit, else it will stay in loop
    while(*shm != '*'){
        sleep(1);
    }
    
    return 0;
}
