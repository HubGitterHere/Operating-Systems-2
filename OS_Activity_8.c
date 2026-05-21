#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#define MAX 15



int scheduling(int arr[], int size){
    int diskHead = arr[0];
    int movement = 0;
    for(int i=1; i< size; i++){
        movement += abs(diskHead-arr[i]);
        diskHead = arr[i];
        printf("current movement: %d\n", movement);
    }
    return movement;
}
int sorting(int arr[], int size){
    int diskHead = arr[0];
    int *lowerArr = (int*) malloc(size *sizeof(int));
    int lowerArrSize = 0;
    for(int i=1; i<size; i++){
        if(arr[i] < diskHead){
            
        }
    }

}
int main(int argc, char *argv[])
{
    int size = 10;
    int FCFS_array[] = {228,46,83,234,245,103,156,133,174,64};
    
    printf("First come first serve scheduling\n");
    scheduling(FCFS_array, size);

    int SCAN_array[] = {228,174,156,133,103,83,64,46,234,245};
    printf("Scan scheduling\n");
    scheduling(SCAN_array, size);
    
    return 0;
}