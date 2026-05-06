
#include <stdio.h>
#include <stdint.h>
#ifdef _WIN32
#include <io.h>
#include <process.h>
#else
#include <unistd.h>
#endif
#include <stdlib.h>
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
int main(int argc, char *argv[])
{
    //*printBanner1();
    return 0;
}
