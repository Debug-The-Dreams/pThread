#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex2 = PTHREAD_MUTEX_INITIALIZER;

void* thread1(void* arg) {
    pthread_mutex_lock(&mutex1);              ///mutex1 locked
    pthread_mutex_lock(&mutex2);
    printf("Doing work\n");
    pthread_mutex_unlock(&mutex2);
    pthread_mutex_unlock(&mutex1);
    return NULL;
}
void* thread2(void* arg) {
    pthread_mutex_lock(&mutex2);           // mutex2 locked 
    pthread_mutex_lock(&mutex1);
    printf("Doing work\n");
    pthread_mutex_unlock(&mutex1);
    pthread_mutex_unlock(&mutex2);
    return NULL;
}

int main() {
    pthread_t t1, t2;
    pthread_create(&t1, NULL, thread1, &mutex1);
    pthread_create(&t2, NULL, thread2, &mutex2);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_mutex_destroy(&mutex1);
    return 0;
}