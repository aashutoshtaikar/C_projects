#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>

pthread_mutex_t lock;


char a[10]; //common buffer

void* myfunc(void* dat); //write to buffer
void* myfunc2(void* dat); //read from buffer and print

int main(int argc, char const *argv[])
{
    pthread_t thread1,thread2;
    char* msg1 = "First thread";
    char* msg2 = "Second thread";
    int ret1,ret2; 

    memset(a, 0, sizeof(a));

    ret1 = pthread_create(&thread1, NULL, myfunc,(void*)msg1);
    ret2 = pthread_create(&thread2, NULL, myfunc2,(void*)msg2);

    pthread_join(thread1,NULL);
    pthread_join(thread2,NULL);

    printf("%s returned %d\n",msg1,ret1);
    printf("%s returned %d\n",msg2,ret2);

    return 0;
}

void* myfunc(void* dat){
    char* msg = (char*) dat;
    
    pthread_mutex_lock(&lock);
    printf("msg: %s\n",msg);

    for(int i = 0; i < 10; i++){
        printf("X"); //writing something
        a[i] = i; 
        
    }
    pthread_mutex_unlock(&lock);

    return NULL;
}

void* myfunc2(void* dat){
    
    pthread_mutex_lock(&lock);
    char* msg = (char*) dat;
    printf("msg: %s\n",msg);

    for(int i = 0; i < 10; i++)
    {
        printf("%d, ",a[i]);
    }
    printf("\n");
    pthread_mutex_unlock(&lock);

    return NULL;
}