#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#define MAX 5

//int addArray(int *iArray)
void *addArray1(void * arg)
{
    int *iArray = (int *) arg;
    int *total = (int *) calloc(1, sizeof(int));
    for (int i = 0; i < MAX; i++) {
		printf("adding array[%d] = %d  ...\n", i, *(iArray+i));
	    (*total) += *(iArray+i);
    }
    return (void *) total;
}
void *addArray2(void * arg)
{
    int *iArray = (int *) arg;
    int begin = *(iArray);
    int end = *(iArray+1);
    int *total = (int *) calloc(1, sizeof(int));
    for (int i = begin+2; i < end+2; i++) {
		printf("adding array[%d] = %d  ...\n", i, *(iArray+i));
	    (*total) += *(iArray+i);
    }
    return (void *) total;
}

int main(int argc, char *argv[])
{
	int array[MAX+2];
	int *result;
    pthread_t p1, p2;
    int beg = 1;
    int end = 3;

    for (int i = 0; i < MAX; i++) {
		array[i] = 2*i+1;
	}

    pthread_create(&p1, NULL, addArray1, (void *) array);
    pthread_join(p1, (void **) &result);
//    result = addArray(array);
	printf("The sum of the array elements is = %d.\n", *result);

    array[0] = beg;
    array[1] = end;
    for (int i = 2; i < MAX+2; i++) {
		array[i] = 2*i+1;
	}
    pthread_create(&p2, NULL, addArray2, (void *) array);
    pthread_join(p2, (void **) &result);
	printf("The sum of the array between [%d] and [%d] elements is = %d.\n", beg, end, *result);

    return 0;
}
