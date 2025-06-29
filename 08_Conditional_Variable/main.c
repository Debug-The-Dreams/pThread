#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int shoot = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
void* shooting(void* arg)
{
    pthread_mutex_lock(&mutex);
    shoot+=1;
    printf("Shooting completed: %d\n", shoot);
    pthread_cond_signal(&cond); // Signal that an episode is available
    pthread_mutex_unlock(&mutex);
    return NULL;
}

void* watchEpisod(void* arg)
{
    pthread_mutex_lock(&mutex);
    while(shoot <= 0) {
        printf("No episodes to watch.\n");
        pthread_cond_wait(&cond, &mutex);
    }
    shoot-=1;
    printf("watched episod, %d.\n", shoot);
    pthread_mutex_unlock(&mutex);
    return NULL;
}


int main()
{
    pthread_t threads[2];

    // Create shooting thread
    if (pthread_create(&threads[0], NULL, shooting, NULL) != 0) {
        perror("Failed to create shooting thread");
        exit(EXIT_FAILURE);
    }       

    // Create watching episode thread
    if (pthread_create(&threads[1], NULL, watchEpisod, NULL  ) != 0) {
        perror("Failed to create watching episode thread");
        exit(EXIT_FAILURE);
    }   

    // Wait for both threads to finish
    for (int i = 0; i < 2; i++) {
        if (pthread_join(threads[i], NULL) != 0) {
            perror("Failed to join thread");
            exit(EXIT_FAILURE);
        }
    }

    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond);
    printf("All threads completed successfully.\n");
    return EXIT_SUCCESS;
}