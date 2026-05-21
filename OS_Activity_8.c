#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#define MAX 15



void FCFSscheduling(int arr[], int size){
    int diskHead = arr[0];
    int movement = 0;
    printf("current movements: ");
    for(int i=1; i< size; i++){
        movement += abs(diskHead-arr[i]);
        diskHead = arr[i];
        printf("%d, ", movement);
    }
    printf("\n");
}
//based off of AI overview
void sorting(int arr[], int size){
    for(int i = 0; i<size; i++){
        for(int j=0; j< size-1;j++){
            if(arr[j] > arr[j+1]){
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1]=temp;
            }
        }
    }

}
int main(int argc, char *argv[])
{
    int size = 10;
    int FCFS_array[] = {228,46,83,234,245,103,156,133,174,64};
    //print first come first serve scheduling
    printf("First come first serve scheduling\n");
    FCFSscheduling(FCFS_array, size);
    //print SCAN scheduling
    int SCAN_array[size];
    for (int i=0; i<size; i++){
        SCAN_array[i] = FCFS_array[i];
    }
    sorting(SCAN_array, size);
    int diskHead = FCFS_array[0];

    for (int i = 0; i < size; i++){
        printf("%d\n", SCAN_array[i]);
    }
    
    return 0;
}