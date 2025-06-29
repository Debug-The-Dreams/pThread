#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<semaphore.h>

int shared_data = 0;
sem_t semaphore;

void* thread_func(void* arg)
{
    sem_wait(&semaphore); // Wait (decrement) the semaphore
    shared_data++;
    printf("Thread %ld incremented shared_data to %d\n", (long)arg, shared_data);
    sem_post(&semaphore); // Signal (increment) the semaphore
    sleep(3); // Simulate some work
    return NULL;
}

int main()
{
    pthread_t threads[8];
    sem_init(&semaphore, 0, 4); // Initialize semaphore with value

    for (long i = 0; i < 8; i++) {
        pthread_create(&threads[i], NULL, thread_func, (void*)i);
    }

    for(int i = 0; i < 8; i++) {
        pthread_join(threads[i], NULL);
    }
    sem_destroy(&semaphore); // Clean up semaphore
    return 0;
}
