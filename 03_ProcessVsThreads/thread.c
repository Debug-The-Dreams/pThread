#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
int shared_variable = 0; // Example of a shared variable
void* thread_function(void* arg) {
    shared_variable+=1;
    sleep(2);
    return NULL;
}

void* thread_function2(void* arg) {
    sleep(2);
    printf("Shared_var = %d\n", shared_variable);
    return NULL;
}

int main() {
    pthread_t thread, thread2;
    
    // Create a new thread
    if (pthread_create(&thread, NULL, thread_function, NULL) != 0) {
        perror("Failed to create thread");
        return 1;
    }
    
    // Wait for the thread to finish
    if (pthread_join(thread, NULL) != 0) {
        perror("Failed to join thread");
        return 1;
    }
    
        if (pthread_create(&thread2, NULL, thread_function2, NULL) != 0) {
        perror("Failed to create thread");
        return 1;
    }
    
    // Wait for the thread to finish
    if (pthread_join(thread2, NULL) != 0) {
        perror("Failed to join thread");
        return 1;
    }
    printf("Thread has finished execution.\n");
    return 0;
}

//definition 
//memory
//isolation
//communication
//overhead
//crash impact
//Examples