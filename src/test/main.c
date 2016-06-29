#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <eknnwindev.h>

#define N 5000
#define K 2500

#define RAND //RAND or STATIC

#ifdef STATIC
#define N 6
#endif

int main(int argc, char **argv)
{
	srand(time(NULL));

	double **points = NULL;
	points = (double**) malloc(N*sizeof(double*));

	for(unsigned long i = 0 ; i < N ; i++)
	{
		points[i] = (double*) malloc(2*sizeof(double));
#ifdef RAND
		points[i][0] = ((float)rand()/(float)(RAND_MAX/20))-10;
		points[i][1] = ((float)rand()/(float)(RAND_MAX/20))-10;
#endif
	}

#ifdef STATIC
	points[0][0] = 0;
	points[0][1] = 9;
	points[1][0] = 4;
	points[1][1] = 1;
	points[2][0] = 7;
	points[2][1] = -7;
	points[3][0] = -4;
	points[3][1] = -4;
	points[4][0] = -1;
	points[4][1] = 0;
	points[5][0] = 6;
	points[5][1] = 5;
#endif

	EkNNSystem *foo = EkNNInit(points, N, K);
	
	for(unsigned long i = 0 ; i < N ; i++)
		free(points[i]);
	free(points);

	printf("\n\nCLUSTERIZE\n\n");
	EkNNClusterize(foo);
	printf("\n\nDONE\n\n");

	//EkNNDisplay(foo);
	EkNNExportToCSV(foo, "./foo.csv");

	EkNNDestroy(foo);
	
	return 0;
}
