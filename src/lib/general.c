#include "eknnwindev.h"

void EkNNDisplay(EkNNSystem *foo)
{
	printf("points=\n");
	for(unsigned long i = 0 ; i < foo->N ; i++)
		printf("(%f,%f): #%lu\n", foo->points[i].x, foo->points[i].y, foo->points[i].cluster);

	printf("\ndistances=\n");
	for(unsigned long i = 0 ; i < foo->N ; i++)
	{
		for(unsigned long j = 0 ; j < foo->N ; j++)
			printf("%f ", foo->distances[i][j]);
		printf("\n");
	}

	printf("\nkNN=\n");
	for(unsigned long i = 0 ; i < foo->N ; i++)
	{
		for(unsigned long j = 0 ; j < foo->K ; j++)
			printf("%lu ", foo->kNN[i][j]);
		printf("\n");
	}

	printf("\ngamma=\n%f\n", foo->gamma);
	
	printf("\nalpha=\n");
	for(unsigned long i = 0 ; i < foo->N ; i++)
	{
		for(unsigned long j = 0 ; j < foo->K ; j++)
			printf("%f ", foo->alpha[i][j]);
		printf("\n");
	}

	printf("\nv=\n");
	for(unsigned long i = 0 ; i < foo->N ; i++)
	{
		for(unsigned long j = 0 ; j < foo->K ; j++)
			printf("%f ", foo->v[i][j]);
		printf("\n");
	}
}

void EkNNClusterize(EkNNSystem *system)
{
	bool flag = TRUE;
	unsigned long *sigma = (unsigned long*) malloc(system->N*sizeof(unsigned long));
	for(unsigned long i = 0 ; i < system->N ; i++)
		sigma[i] = i;

	while(flag == TRUE)
	{
		flag = FALSE;

		double **u = (double**) malloc(system->N*sizeof(double*));
		for(unsigned long i = 0 ; i < system->N ; i++)
		{
			u[i] = (double*) malloc(system->C*sizeof(double));
			for(unsigned long j = 0 ; j < system->C ; j++)
				u[i][j] = 0;
		}
		
		toss(sigma, system->N, 2*system->N);

		for(unsigned long i = 0 ; i < system->N ; i++)
		{
			double max = 0;
			unsigned long kstar = 1;

			for(unsigned long k = 0 ; k < system->C ; k++)
			{
				for(unsigned long j = 0 ; j < system->K ; j++)
					if(system->points[system->kNN[sigma[i]][j]].cluster == k+1)
						u[sigma[i]][k]+= system->v[sigma[i]][j];

				if(u[sigma[i]][k] >= max)
				{
					max = u[sigma[i]][k];
					kstar = k+1;
				}
			}

			if(system->points[sigma[i]].cluster != kstar)
			{
				system->points[sigma[i]].cluster = kstar;
				flag = TRUE;
			}
		}
		EkNNUpdateC(system);
		for(unsigned long i = 0 ; i < system->N ; i++)
			free(u[i]);
		free(u);
	
		if(system->C == 1)
		{
			fprintf(stderr, "EkNNClusterize: Gave only one cluster, please try again\n");
			exit(1);
		}
	}

	free(sigma);
}

