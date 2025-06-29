//ek mutext  writer exclusive access 
//reader counter
//reader mutex


#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

pthread_mutex_t writer_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t reader_mutex = PTHREAD_MUTEX_INITIALIZER;
int reader_count = 0;   

int shared_data = 1; // Shared data that readers and writers will access


void* writer(void* arg) {
    pthread_mutex_lock(&writer_mutex);
    sleep(1); // Simulate some writing time
    shared_data *= 5;
    printf("Writer %ld: Updated shared_data = %d\n", (long)arg, shared_data);
    pthread_mutex_unlock(&writer_mutex);
    return NULL;
}

void* reader(void* arg)
{
    pthread_mutex_lock(&reader_mutex);
    reader_count++;
    if (reader_count == 1) {
        pthread_mutex_lock(&writer_mutex); // First reader locks the writer mutex
    }
    pthread_mutex_unlock(&reader_mutex);

    // Reading shared data
    sleep(1); // Simulate some reading time
    printf("Reader %ld: Read shared_data = %d\n", (long)arg, shared_data);

    pthread_mutex_lock(&reader_mutex);
    reader_count--;
    if (reader_count == 0) {
        pthread_mutex_unlock(&writer_mutex); // Last reader unlocks the writer mutex
    }
    pthread_mutex_unlock(&reader_mutex);
    return NULL;
}

int main() {
    pthread_t readers[5], writers[2];
    
    // Create writer threads
    for (long i = 0; i < 2; i++) {
        pthread_create(&writers[i], NULL, writer, (void*)i);
    }

    // Create reader threads
    for (long i = 0; i < 5; i++) {
        pthread_create(&readers[i], NULL, reader, (void*)i);
    }

    // Join writer threads
    for (int i = 0; i < 2; i++) {
        pthread_join(writers[i], NULL);
    }

    // Join reader threads
    for (int i = 0; i < 5; i++) {
        pthread_join(readers[i], NULL);
    }

    printf("Final shared_data value: %d\n", shared_data);
    
    // Destroy mutexes
    pthread_mutex_destroy(&writer_mutex);
    pthread_mutex_destroy(&reader_mutex);
    return 0;
}