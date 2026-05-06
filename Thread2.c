#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <stdlib.h>
#define MAX 5

int addArray(int *iArray)
{
    int total = 0;
    for (int i = 0; i < MAX; i++) {
		printf("adding array[%d] = %d  ...\n", i, *(iArray+i));
	    total += *(iArray+i);
    }
    return total;
}

int main(int argc, char *argv[])
{
	int array[MAX];
	int result;

    for (int i = 0; i < MAX; i++) {
		array[i] = 2*i+1;
	}

    result = addArray(array);
	printf("The sum of the array elements is = %d.\n", result);

    return 0;
}
