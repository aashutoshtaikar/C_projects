#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>

void* myfunc(void* dat);

int main(int argc, char const *argv[])
{
    pthread_t thread1,thread2;
    char* msg1 = "First thread";
    char* msg2 = "Second thread";
    int ret1,ret2; 
    
    ret1 = pthread_create(&thread1, NULL, myfunc,(void*)msg1);
    ret2 = pthread_create(&thread2, NULL, myfunc,(void*)msg2);

    printf("Main function after pthread create\n");
    pthread_join(thread1,NULL);
    pthread_join(thread2,NULL);

    printf("%s %d\n",msg1,ret1);
    printf("%s %d\n",msg2,ret2);

    return 0;
}

void* myfunc(void* dat){
    char* msg = (char*) dat;
    for(int i = 0; i < 10; i++)
    {
        printf("%s %d\n",msg,i);
        sleep(1); //causes interleave of printing from each thread
    }
    return NULL;
}
