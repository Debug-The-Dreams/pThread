#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

/* Increment the character
    mov al, [order] ; Load char into al          //thread1 and thread2 
    inc al           ; Increment
    mov [order], al ; Store back
*/
pthread_mutex_t mutex;
const int MAX = 500000;
int order = 0;

void* thread_function(void* arg) {
    for(int i=0; i < MAX; i++) {
        pthread_mutex_lock(&mutex); // Lock the mutex before accessing shared resource
        order++;
        pthread_mutex_unlock(&mutex); // Unlock the mutex after accessing shared resource
    }
    return NULL;
}

int main() {
    // Initialize the thread
    pthread_t thread, thread2;
    pthread_mutex_init(&mutex, NULL);
    // Create a new thread
    if (pthread_create(&thread, NULL, thread_function, NULL) != 0) {
        perror("Failed to create thread");
        return EXIT_FAILURE;
    }

    if (pthread_create(&thread2, NULL, thread_function, NULL) != 0) {
        perror("Failed to create thread");
        return EXIT_FAILURE;
    }

    // Wait for the thread to finish
    if (pthread_join(thread, NULL) != 0) {
        perror("Failed to join thread");
        return EXIT_FAILURE;
    }

        // Wait for the thread to finish
    if (pthread_join(thread2, NULL) != 0) {
        perror("Failed to join thread");
        return EXIT_FAILURE;
    }

    printf("Total Ordered received = %d.\n", order);
    pthread_mutex_destroy(&mutex);
    return EXIT_SUCCESS;
}