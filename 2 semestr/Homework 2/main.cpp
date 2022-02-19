#include <iostream>
#include <pthread.h>
#include <unistd.h>
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t isReadyToPrint = PTHREAD_COND_INITIALIZER;
bool isReady = false;

void* PrintPong(void*)
{
    pthread_mutex_lock(&mutex);
    while (!isReady)
    {
        pthread_cond_wait(&isReadyToPrint , &mutex);
    }
    std::cout << "Pong" << std::endl;
    pthread_mutex_unlock(&mutex);
    return NULL;
}

void* PrintPing(void*)
{
    pthread_mutex_lock(&mutex);
    std::cout<<"Ping"<<std::endl;
    isReady = true;
    pthread_cond_signal(&isReadyToPrint);
    pthread_mutex_unlock(&mutex);
    return NULL;
}

int main()
{
    pthread_t thread1 , thread2;
    while(true)
    {
    	pthread_create(&thread1 , NULL , PrintPing , NULL);
    	sleep(1);
    	pthread_create(&thread2 , NULL , PrintPong , NULL);
    	sleep(1);
    	pthread_join(thread1 , NULL);
   	pthread_join(thread2 , NULL);
    }
    
    return 0;
}
