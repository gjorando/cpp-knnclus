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
				printf("3> Import from dataset\n");
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
	printf("\nPlease type any character and press Enter to continue...\n");
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

void importFromDataset(EkNNSystem **f)
{
	FILE *dataset = NULL;
	unsigned long n, k, nDef;
	double **points = NULL;
	
	CLEAR_SCREEN();
	printf("===IMPORT FROM DATASET===\n\n");
	printf("N=");
	scanf("%lu", &n);
	printf("K=");
	scanf("%lu", &k);
	
	points = (double**) malloc(n*sizeof(double*));
	for(unsigned long i = 0 ; i < n ; i++)
		points[i] = (double*) malloc(2*sizeof(double));
	
	if((dataset = fopen("res/dataset.csv", "r")) == NULL)
	{
		fprintf(stderr, "fopen: unable to open res/dataset.csv\n");
		exit(1);
	}

	printf("\nImporting %lu lines...\n", n);

	unsigned long i = 0, s = 0;
	char c;
	char *buf = NULL;

	while((c = fgetc(dataset)) != '\n' && c != EOF); //Reads the first line (labels)
	do //Reads the n next lines (or until it reaches EOF)
	{
		s++;
		c = fgetc(dataset);
		buf = (char*) realloc(buf, s*sizeof(char));
		buf[s-1] = c;
		if(c == '\n') //When you got an entire line
		{
			int countSemiColon = 0;
			unsigned long j = 0;
			while(countSemiColon < 4) //go to after the 4th semi-colon (entry containing the value for CO2)
				if(buf[j++] == ';') countSemiColon++;
			
			unsigned long jM = j-1;
			while(buf[++jM] != ';'); //reaches the next semi-colon
			
			unsigned long CO2Len = jM-j;
			if(CO2Len != 0) //The line is skipped if we have a missing value
			{
				char *CO2 = (char*) malloc(1+CO2Len*sizeof(char));
				for(unsigned long k = j ; k < jM ; k++) //We copy the value of the CO2 in the buffer into our string
					CO2[k-j] = buf[k];
				CO2[CO2Len] = '\0';

				j = jM+1;
				jM = j-1;
				while(buf[++jM] != ';'); //reaches the next semi-colon
				unsigned long noiseLen = jM-j;
				if(noiseLen != 0) //The line is skipped if we have a missing value
				{
					char *noise = (char*) malloc(1+noiseLen*sizeof(char));
					for(unsigned long k = j ; k < jM ; k++)
						noise[k-j] = buf[k];
					noise[noiseLen] = '\0';
					
					//Ok, so now we got our values in strings
					
					double noiseD = (double) atoi(noise);
					double CO2D = (double) atoi(CO2);
				
					points[i][0] = noiseD;
					points[i][1] = CO2D;
					
					i++;

					free(noise);
				}

				free(CO2);
			}

			free(buf);
			buf = NULL;
			s = 0;
		}
	}
	while(i < n && c != EOF);
	nDef = i;
	printf("\n%lu were read.\n", nDef);
	printf("\nPerforming initialisation...\n");
	*f = EkNNInit(points, nDef, k);

	printf("\nFreeing temporary points...\n");
	for(unsigned long i = 0 ; i < n ; i++)
		free(points[i]);
	free(points);

	fclose(dataset);
}
