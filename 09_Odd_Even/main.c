// ek thread odd numbers
// dusara thread even numbers
// condition sequence

#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

#define MAX 1000000
int number = 0; // Shared variable
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;


void* printOdd(void* arg) {

    while (number <= MAX) {
        sleep(1); // Sleep to allow even thread to run
        pthread_mutex_lock(&mutex);
        if (number % 2 == 1) {
            printf("Odd: %d\n", number);
        }

        number++;
        pthread_mutex_unlock(&mutex);   
        pthread_cond_signal(&cond); // Signal the even thread
    }
    return NULL;
}

void* printEven(void* arg) {

    while (number <= MAX) {
        pthread_mutex_lock(&mutex);
        while (number % 2 == 1) { // Wait for the odd thread to finish
            pthread_cond_wait(&cond, &mutex);
        }
        if (number % 2 == 0) {
            printf("Even: %d\n", number);
        }
        number++;
        pthread_mutex_unlock(&mutex);
        sleep(1); // Sleep to allow odd thread to run
    }
    return NULL;
}

int main()
{
    pthread_t oddThread, evenThread;

    // Create threads
    pthread_create(&oddThread, NULL, printEven, NULL);
    pthread_create(&evenThread, NULL, printOdd, NULL);         

    // Wait for threads to finish
    pthread_join(oddThread, NULL);  
    pthread_join(evenThread, NULL);
    
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond);
    return EXIT_SUCCESS;
}