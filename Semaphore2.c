#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>

pthread_mutex_t lockArrays;
pthread_cond_t condStage;

// Input:{Number of sides, length of one side}
volatile float input[] = { 0.0, 0.0 };
// Output: {area, perimeter, shortest distance bewtween non-adjacent vertices}
volatile float output[] = { 0.0, 0.0, 0.0 };
// global variable for ordering
   int stage = 0;


// Calculates the area of a regular polygon
void *area(void *arg)
{
	pthread_mutex_lock(&lockArrays);
		// Critical Section
	    double a = (input[1] * input[1] * input[0])/(4.0*tan((double) (M_PI/input[0])));
	    output[0] = (float) a;
		printf("Setting value of area = %.2f \n", output[0]);
		stage = 1;
		pthread_cond_signal(&condStage);
	    // End of Critical Section
	pthread_mutex_unlock(&lockArrays);
    return NULL;
}

// Caluclates the perimeter of a regular polygon
void *perimeter(void *arg)
{
	pthread_mutex_lock(&lockArrays);
	while (stage < 1) pthread_cond_wait(&condStage, &lockArrays);
		// Critical Section
	    output[1] = input[0]*input[1];
		printf("Setting value of perimeter = %.2f \n", output[1]);
		stage = 2;
		pthread_cond_signal(&condStage);
	    // End of Critical Section
	pthread_mutex_unlock(&lockArrays);
    return NULL;
}

// Caculates the shortest distance between two non-adjacent vertices
void *distance(void *arg)
{
	pthread_mutex_lock(&lockArrays);
	while (stage < 2) pthread_cond_wait(&condStage, &lockArrays);
		// Critical Section
	    double a = (2.0 * input[1] * sin((double) (M_PI/input[0])));
	    output[2] = (float) a;
		printf("Setting value of smallest distance between non consecutive vertices = %.2f \n", output[2]);
	    // End of Critical Section
	pthread_mutex_unlock(&lockArrays);
    return NULL;
}

int main(int argc, char *argv[])
{
    // Default input a Triangle of side 2
    input[0] = 3.0;
    input[1] = 2.0;

    //Reading parameters from the command line
    if (argc > 1) {                   // number of sides
	    input[0] = atof(argv[1]);
    }
    if (argc > 2) {                   // length of a side
	    input[1] = atof(argv[2]);
    }

    if (pthread_mutex_init(&lockArrays, NULL)!=0) { ;
		printf("Lock could not be initialized.\n");
		return -1;
	}


    // Creating separated threads for calculation
    pthread_t p1,p2, p3;
    pthread_create(&p1, NULL, area, (void *) NULL);
    pthread_create(&p2, NULL, perimeter, (void *) NULL);
    pthread_create(&p3, NULL, distance, (void *) NULL);

    // waiting for all threads to end
    pthread_join(p1, NULL);
    pthread_join(p2, NULL);
    pthread_join(p3, NULL);

	printf("\nResults in main\n");
    printf("A polygon with %d sides of length %.2f has:\n", (int) input[0], input[1]);
	printf("Area = %.2f\n", output[0]);
	printf("Perimeter = %.2f\n", output[1]);
	printf("Smallest distance between non consecutive vertices = %.2f\n", output[2]);
    return 0;
}
