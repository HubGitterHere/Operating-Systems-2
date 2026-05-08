#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

//pthread_mutex_t lockRand = PTHREAD_MUTEX_INITIALIZER;
sem_t semaphore;

volatile int rand_value = 0;

void * changeValue(void *arg)
{
    int times = (int) arg;
    for (int i = 0; i < times; i++) {
        //pthread_mutex_lock(&lockRand);
        sem_wait(&semaphore);
        // Critical Section
	        rand_value = rand();
		    printf("%d Value changed to: %d]\n", i+1,rand_value);
        // End of Critical Section
        //pthread_mutex_unlock(&lockRand);
        sem_post(&semaphore);
        usleep(300);
    }
    printf("changeValue ended\n");
    return NULL;
}
void * checkValue(void *arg)
{
    int times = (int) arg;
    for (int i = 0; i < 2*times; i++) {
        //pthread_mutex_lock(&lockRand);
        sem_wait(&semaphore);
        // Critical Section
	    printf("           Value found: %d]\n", rand_value);
        // End of Critical Section
        //pthread_mutex_unlock(&lockRand);
        sem_post(&semaphore);
        usleep(100);
	}
    return NULL;
}

int main(int argc, char *argv[])
{
	int times;
    if (argc != 2) {
        fprintf(stderr, "usage: progname <times to run>\n");
        exit(1);
    }
    times = atoi(argv[1]);

    sem_init(&semaphore, 0, 1);

    pthread_t p1, p2;
    pthread_create(&p1, NULL, changeValue, (void *) times);
    pthread_create(&p2, NULL, checkValue, (void *) times);
    // join waits for the threads to finish
    pthread_join(p1, NULL);
    pthread_join(p2, NULL);
    return 0;
}
