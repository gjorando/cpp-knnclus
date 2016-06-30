#include "functions.h"

void displayMenu(int *choice, int max, int mode)
{
	int goodChoice = 1;

	do
	{
		CLEAR_SCREEN();
		printf("===DEMONSTRATION FOR C-EKNNWINDEV TEST MODULE===\n\n");
	
		switch(mode)
		{
			case 1:
				printf("1> New random EkNNSystem\n");
				printf("2> New EkNNSystem\n");
				break;
			case 2:
				printf("1> Clusterize\n");
				printf("2> Print state\n");
				printf("3> Delete EkNNSystem\n");
				printf("4> Export to CSV\n");
				break;
			default:
				break;
		}
		printf("%d> About\n", max-1);
		printf("%d> Quit\n\n", max);
	
		if(goodChoice == 0) printf("Bad choice. Try again please.\n");
		printf("Your choice ? ");
		scanf("%d", choice);

		if((*choice < 1) || (*choice > max)) goodChoice = 0;
		else goodChoice = 1;
	}while(goodChoice == 0);
}

void printAbout()
{
	const int DURATION = 5;
	CLEAR_SCREEN();
	printf("====ABOUT===\n\n");
	printf("EkNNclus procedure test module\n");
	printf("Author: LTI IUT Amiens, JORANDON Guillaume, ROBILLARD Rémy\n");
	printf("Contact: +33 (0)3 22 53 40 38\n\n");
	for(int i = 0 ; i < DURATION ; i++)
	{
		printf("%d...", DURATION-i);
		fflush(stdout);
		sleep(1);
	}
}

void initRandomSystem(EkNNSystem **f)
{
	double **points = NULL;
	unsigned long n, k;

	CLEAR_SCREEN();
	printf("===NEW RANDOM EkNNSystem===\n\n");
	printf("N=");
	scanf("%lu", &n);
	printf("K=");
	scanf("%lu", &k);
	
	points = (double**) malloc(n*sizeof(double*));

	printf("\nCreating a bunch of random points...\n");
	for(unsigned long i = 0 ; i < n ; i++)
	{
		points[i] = (double*) malloc(2*sizeof(double));
		points[i][0] = ((float)rand()/(float)(RAND_MAX/20))-10;
		points[i][1] = ((float)rand()/(float)(RAND_MAX/20))-10;
	}

	printf("\nPerforming initialisation...\n");
	*f = EkNNInit(points, n, k);

	printf("\nFreeing temporary points...\n");
	for(unsigned long i = 0 ; i < n ; i++)
		free(points[i]);
	free(points);

	printf("\nDone!\n");
}

void deleteSystem(EkNNSystem *f)
{
	CLEAR_SCREEN();
	printf("===DELETE EkNNSystem===\n\n");
	printf("Freeing the EkNNSystem...\n");
	if(f != NULL)
		EkNNDestroy(f);
	else
		fprintf(stderr, "(!)GRAVE: An unknown misfunction occurred.\n");

	printf("\nDone!\n");
}

void printState(EkNNSystem *f)
{
	CLEAR_SCREEN();
	printf("===CURRENT STATE===\n\n");
	EkNNDisplay(f);
	int c;
	printf("Please type any character and press Enter to continue...\n");
	fflush(stdin);
	scanf("%d", &c);
	fflush(stdin);
}

void clusterize(EkNNSystem *f)
{

	CLEAR_SCREEN();
	printf("===CLUSTERIZE===\n\n");
	printf("Clusterizing...\n");
	EkNNClusterize(f);
	printf("\nDone!\n");
	int c;
	printf("Please type any character and press Enter to continue...\n");
	fflush(stdin);
	scanf("%d", &c);
	fflush(stdin);
}

void exportToCSV(EkNNSystem *f)
{
	CLEAR_SCREEN();
	printf("===EXPORT TO CSV===\n\n");
	printf("Exporting...\n");
	EkNNExportToCSV(f, "./build/foo.csv");
	printf("\nDone! The system has been exported to ./build/foo.csv\n");
	int c;
	printf("Please type any character and press Enter to continue...\n");
	fflush(stdin);
	scanf("%d", &c);
	fflush(stdin);
}
