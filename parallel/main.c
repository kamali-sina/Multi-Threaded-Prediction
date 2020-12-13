#include <stdio.h>
#include <stdlib.h>

#include <pthread.h>

typedef struct 
{
	double* a;
	double* b;
	double sum; 
	int length; 
} DOT_DATA;


#define NUMBER_OF_THREADS 4
#define LENGTH 1e7
DOT_DATA dot_product_result; 
pthread_t threads[NUMBER_OF_THREADS];
pthread_mutex_t mutex_sum;

#define RESET_COLOR_INDEX 4

char COLOR_CODES[5][255] =
{
	"\033[1m\033[30m",		// Bold BLACK
	"\033[1m\033[31m",		// Bold RED
	"\033[1m\033[32m",		// Bold GREEN
	"\033[1m\033[34m",		// Bold BLUE
	"\x1B[0m"				// Reset
};

int main (int argc, char *argv[])
{
	void *status;

	/* Assign storage and initialize values */

	double* a = (double*)malloc (NUMBER_OF_THREADS *
			LENGTH * sizeof(double));
	double* b = (double*)malloc (NUMBER_OF_THREADS *
			LENGTH * sizeof(double));

	for(long i = 0; i < LENGTH * NUMBER_OF_THREADS; i++)
		b[i] = a[i] = 1;

	dot_product_result.length = LENGTH;
	dot_product_result.a = a; 
	dot_product_result.b = b; 
	dot_product_result.sum = 0;

	pthread_mutex_init(&mutex_sum, NULL);

	for(long i = 0; i < NUMBER_OF_THREADS; i++)
		// pthread_create(&threads[i], NULL, dot_product, (void*)i); 

	/* Wait on the other threads */
	for(long i = 0; i < NUMBER_OF_THREADS; i++)
		pthread_join(threads[i], &status);
	
	/* After joining, print out the results and cleanup */
	printf("Sum =  %f \n", dot_product_result.sum);
	free(a);
	free(b);
	pthread_mutex_destroy(&mutex_sum);
	pthread_exit(NULL);
}