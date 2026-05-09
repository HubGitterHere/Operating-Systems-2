#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#define MAX 5
//pthread_mutex_t lockRand = PTHREAD_MUTEX_INITIALIZER;
sem_t semaphore;

volatile int schedules[] = {6, 7, 8};

void *checkSchedule1(void *arg)
{
	int times = 20;
	int rand_value;
		printf("Thread 1 working ... ");
        rand_value = (rand() % MAX);
		printf("waiting %d seconds\n",rand_value);
        usleep(rand_value*100000); //sleep time in microseconds

    return NULL;
}
void *checkSchedule2(void *arg)
{
	int times = (int) arg;
	int rand_value;
		printf("                    Thread 2 working ... ");
        rand_value = (rand() % MAX);
		printf("waiting %d seconds\n",rand_value);
        usleep(rand_value*100000); //sleep time in microseconds
    return NULL;
}
void *checkSchedule3(void *arg)
{
	int times = 20;
	int rand_value;
		printf("                                    Thread 3 working ... ");
        rand_value = (rand() % MAX);
		printf("waiting %d seconds\n",rand_value);
        usleep(rand_value*100000); //sleep time in microseconds
    return NULL;
}
void *checkSchedule4(void *arg)
{
	int times = (int) arg;
	int rand_value;
		printf("                                                    Thread 4 working ... ");
        rand_value = (rand() % MAX);
		printf("waiting %d seconds\n",rand_value);
        usleep(rand_value*100000); //sleep time in microseconds
    return NULL;
}
int main(int argc, char *argv[])
{
    int times = 5;

    sem_init(&semaphore, 0, 1);

    pthread_t p1, p2, p3, p4;
    pthread_create(&p1, NULL, checkSchedule1, (void *) NULL);
    pthread_create(&p2, NULL, checkSchedule2, (void *) NULL);
    pthread_create(&p3, NULL, checkSchedule3, (void *) NULL);
    pthread_create(&p4, NULL, checkSchedule4, (void *) NULL);
    // join waits for the threads to finish
    pthread_join(p1, NULL);
    pthread_join(p2, NULL);
    pthread_join(p3, NULL);
    pthread_join(p4, NULL);
    return 0;
}