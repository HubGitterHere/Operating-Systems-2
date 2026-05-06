#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#define MAX 5

void *printBanner1(void *arg)
{
	int times = 20;
	int rand_value;
	for (int i=0; i<times; i++) {
		printf("Thread 1 working ... ");
        rand_value = (rand() % MAX)*100000;
		printf("waiting %d microseconds\n",rand_value);
        usleep(rand_value); //sleep time in microseconds
    }
    return NULL;
}
void *printBanner2(void *arg)
{
	int times = (int) arg;
	int rand_value;
	for (int i=0; i<times; i++) {
		printf("                    Thread 2 working ... ");
        rand_value = (rand() % MAX)*100000;
		printf("waiting %d microseconds\n",rand_value);
        usleep(rand_value); //sleep time in microseconds
    }
    return NULL;
}
int main(int argc, char *argv[])
{
    pthread_t p1, p2;
    int times = 30;

    pthread_create(&p1, NULL, printBanner1, (void *) NULL);
    pthread_create(&p2, NULL, printBanner2, (void *) times);
    pthread_join(p2, NULL);
    pthread_join(p1, NULL);
    //*printBanner1((void *) NULL);
    return 0;
}
