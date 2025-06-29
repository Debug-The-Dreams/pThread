#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<semaphore.h>

#define BUFFER_SIZE 10 

int buffer[BUFFER_SIZE];
int count = 0;

sem_t empty;
sem_t full;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void* producer(void* arg) {

    do
    {   sleep(1);
        int item = ran()%100;
        sem_wait(&empty);
        pthread_mutex_lock(&mutex);
        buffer[count] = item;
        count++;
        pthread_mutex_unlock(&mutex);
        sem_post(&full);
    } while (1);
    
    return NULL;
}

void* consumer(void* arg) {
    do
    {   sleep(1);
        sem_wait(&full);
        pthread_mutex_lock(&mutex);

        if(count > 0)
        {
            int item = buffer[count - 1];
            count--;
            printf("Consumed: %d\n", item);
        }

        pthread_mutex_unlock(&mutex);
        sem_post(&empty);
    } while (1);
    
    return NULL;
}

int main()
{
    pthread_t prod_thread, cons_thread;

    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);

    pthread_create(&prod_thread, NULL, producer, NULL);
    pthread_create(&cons_thread, NULL, consumer, NULL);

    pthread_join(prod_thread, NULL);
    pthread_join(cons_thread, NULL);

    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&mutex);
    return 0;
}