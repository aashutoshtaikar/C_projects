/* Program illustrates usage of binary semaphore with threads instead of processes */
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>
#include <semaphore.h>

sem_t sem;
char buf[24]; //common buffer

void* myfunc(void* dat); //write to buffer
void* myfunc2(void* dat); //read from buffer and print

int main(int argc, char const *argv[])
{
    memset(buf, 0, sizeof(buf));
    pthread_t thread1,thread2;
    char* msg1 = "First thread";
    char* msg2 = "Second thread";


    sem_init(&sem, 0, 1); //0 -> shared between threads, 1-> binary semaphore

    pthread_create(&thread1, NULL, myfunc,(void*)msg1);
    pthread_create(&thread2, NULL, myfunc2,(void*)msg2);

    pthread_join(thread1,NULL);
    pthread_join(thread2,NULL);

     sem_destroy(&sem);

    return 0;
}

void* myfunc(void* dat){
    
    char* msg = (char*) dat;
    printf("msg: %s\n",msg);

    sem_wait(&sem);
    sprintf(buf,"%s","hello there!!");
    sem_post(&sem);

    pthread_exit(0);
}

void* myfunc2(void* dat){

    char* msg = (char*) dat;
    printf("msg: %s\n",msg);

    sem_wait(&sem);
    printf("%s\n",buf);
    sem_post(&sem);

    pthread_exit(0);
}