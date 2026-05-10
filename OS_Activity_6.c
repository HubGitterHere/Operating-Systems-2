#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#define MAX 15
//pthread_mutex_t lockRand = PTHREAD_MUTEX_INITIALIZER;
sem_t semaphore;

volatile int currentBudget = 50 * 100000;

void *checkBudget1(void *arg)
{
	int times = 10;
	int rand_value;
	for (int i=0; i<times; i++) {
        sem_wait(&semaphore);
		printf("Thread 1 working ... ");
        rand_value = (rand() % MAX)*100000;
        printf("spending %d.", rand_value);
        if (currentBudget >= rand_value){
            currentBudget -= rand_value;
            printf(" Money spent, ");
        }else{
            printf(" Can't spend, ");
        }
		printf("current budget is %d\n",currentBudget);
        sem_post(&semaphore);
        usleep(rand_value); //sleep time in microseconds
    }
    return NULL;
}
void *checkBudget2(void *arg)
{
	int times = 10;
	int rand_value;
	for (int i=0; i<times; i++) {
        sem_wait(&semaphore);
		printf("        Thread 2 working ... ");
        rand_value = (rand() % MAX)*100000;
        printf("spending %d.", rand_value);
        if (currentBudget >= rand_value){
            currentBudget -= rand_value;
            printf(" Money spent, ");
        }else{
            printf(" Can't spend, ");
        }
		printf("current budget is %d\n",currentBudget);
        sem_post(&semaphore);
        usleep(rand_value); //sleep time in microseconds
    }
    return NULL;
}
int main(int argc, char *argv[])
{
    sem_init(&semaphore, 0, 1);

    pthread_t p1, p2;
    pthread_create(&p1, NULL, checkBudget1, NULL);
    pthread_create(&p2, NULL, checkBudget2, NULL);
    // join waits for the threads to finish
    pthread_join(p1, NULL);
    pthread_join(p2, NULL);
    return 0;
}