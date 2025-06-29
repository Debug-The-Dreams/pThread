#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>


#define NUM_THREADS 5

pthread_barrier_t barrier;
void* thread_function(void* arg) {
    int thread_id = *((int*)arg);
    sleep(1); // Simulate some work before printing
    printf("Thread %d is running\n", thread_id);


    sleep(1); // Simulate some work
    printf("Thread %d has finished\n", thread_id);
    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];


    // Create threads
    for (int i = 0; i < NUM_THREADS; i++) {
        if (pthread_create(&threads[i], NULL, thread_function, &i) != 0) {
            perror("Failed to create thread");
            exit(EXIT_FAILURE);
        }
    }

    // Wait for all threads to finish
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("All threads have finished\n");
    return 0;
}