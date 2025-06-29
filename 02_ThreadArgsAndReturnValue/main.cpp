#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

struct thread_args {
    int arg1;
    int arg2;
};

void* thread_function(void* arg)
{
    thread_args* args = (thread_args*) arg;   

    int* result = (int*)malloc(sizeof(int));
    if (result == NULL) {
        perror("Failed to allocate memory");
        pthread_exit(NULL);
    }
    *result = args->arg1 + args->arg2;

    return result;
}

int main()
{   
    thread_args args = {10, 20};
    int* res;
    pthread_t thread;
    pthread_create(&thread, NULL, thread_function, (void*)&args);

    pthread_join(thread, (void**)&res);
    printf("Result from thread: %d\n", *res);
    free(res); // Free the allocated memory for the result
    res = NULL; // Set pointer to NULL after freeing
    return EXIT_SUCCESS;
}