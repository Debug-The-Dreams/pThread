#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int shared_variable = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void* thread_function(void* arg) {

    if(pthread_mutex_trylock(&mutex) == 0)
    {
        printf("Able to lock mutex.\n");
        sleep(1); // Simulate some work with the shared variable
        pthread_mutex_unlock(&mutex);
    }
    else
    {
        printf("Unable to lock mutex, it is already locked by another thread.\n");
    }
    return NULL;
}

int main() {
    pthread_t threads[5];

    // Create 5 threads
    for (int i = 0; i < 5; i++) {
        if (pthread_create(&threads[i], NULL, thread_function, NULL) != 0) {
            perror("Failed to create thread");
            exit(EXIT_FAILURE);
        }
    }

    // Wait for all threads to finish
    for (int i = 0; i < 5; i++) {
        pthread_join(threads[i], NULL);
    }

    pthread_mutex_destroy(&mutex);
    return 0;
}