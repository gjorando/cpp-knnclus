#include "eknnwindev.h"

EkNNSystem *EkNNInit(double **points, unsigned long N, unsigned long K)
{
	EkNNSystem *result = (EkNNSystem*) malloc(sizeof(EkNNSystem));
	
	result->N = N;
	result->K = K;
	result->C = N;

	result->points = (EkNNPoint*) malloc(N*sizeof(EkNNPoint));
	for(unsigned long i = 0 ; i < N ; i++)
	{
		result->points[i].x = points[i][0];
		result->points[i].y = points[i][1];
	}
	EkNNInitClusters(result);
	EkNNInitDistances(result);
	EkNNInitKNN(result);
	EkNNInitGamma(result);
	EkNNInitAlpha(result);
	EkNNInitV(result);

	return result;
}

void EkNNDestroy(EkNNSystem *s)
{
	free(s->points);
	for(unsigned long i = 0 ; i < s->N ; i++)
		free(s->distances[i]);
	free(s->distances);
	for(unsigned long i = 0 ; i < s->N ; i++)
		free(s->kNN[i]);
	for(unsigned long i = 0 ; i < s->N ; i++)
		free(s->alpha[i]);
	free(s->alpha);
	for(unsigned long i = 0 ; i < s->N ; i++)
		free(s->v[i]);
	free(s->v);
	free(s);
}

void EkNNInitClusters(EkNNSystem *result)
{
	unsigned long *clus = (unsigned long*) malloc(result->N*sizeof(unsigned long));

	for(unsigned long i = 0 ; i < result->N ; i++)
		clus[i] = i+1;

	toss(clus, result->N, 1.5*result->N);

	for(unsigned long i = 0 ; i < result->N ; i++)
		result->points[i].cluster = clus[i];

	free(clus);
}

void EkNNInitDistances(EkNNSystem *result)
{
	double **dist = (double**) malloc(result->N*sizeof(double*));
	for(unsigned long i = 0 ; i < result->N ; i++)
		dist[i] = (double*) malloc(result->N*sizeof(double));

	for(unsigned long i = 0 ; i < result->N ; i++)
	{
		dist[i][i] = 0;
		for(unsigned long j = 0 ; j < i ; j++)
		{
			dist[i][j] = distance(result->points[i], result->points[j]);
			dist[j][i] = dist[i][j];
		}
	}

	result->distances = dist;
}

void EkNNInitKNN(EkNNSystem *result)
{
	unsigned long **knn = (unsigned long**) malloc(result->N*sizeof(unsigned long*));
	for(unsigned long i = 0 ; i < result->N ; i++)
		knn[i] = (unsigned long*) malloc(result->K*sizeof(unsigned long));

	for(unsigned long i = 0 ; i < result->N ; i++)
	{
		double *tmpD = (double*) malloc(result->N*sizeof(double));

		for(unsigned long j = 0 ; j < result->N ; j++)
			tmpD[j] = result->distances[i][j];

		unsigned long *tmp = specialSort(tmpD, result->N);
		
		unsigned long j = 0, k = 0; 
		while(j < result->K)
		{
			if(tmpD[k] != 0)
			{
				knn[i][j] = tmp[k];
				j++;
			}
			k++;
		}

		free(tmpD);
		free(tmp);
	}

	result->kNN = knn;
}

void EkNNInitGamma(EkNNSystem *result)
{
	double *dist;
	dist = (double*) malloc(result->K*result->N*sizeof(double));

	unsigned long cpt = 0;

	for(unsigned long i = 0 ; i < result->N ; i++)
		for(unsigned long j = 0 ; j < result->K ; j++)
			dist[cpt++] = result->distances[i][result->kNN[i][j]];

	result->gamma = 1/median(dist, result->K*result->N);

	free(dist);
}

void EkNNInitAlpha(EkNNSystem *result)
{	
	double **a = (double**) malloc(result->N*sizeof(double*));
	for(unsigned long i = 0 ; i < result->N ; i++)
		a[i] = (double*) malloc(result->K*sizeof(double));

	for(unsigned long i = 0 ; i < result->N ; i++)
		for(unsigned long j = 0 ; j < result->K ; j++)
			a[i][j] = exp(-result->gamma*result->distances[i][result->kNN[i][j]]*result->distances[i][result->kNN[i][j]]);

	result->alpha = a;
}

void EkNNInitV(EkNNSystem *result)
{
	double **v = (double**) malloc(result->N*sizeof(double*));
	for(unsigned long i = 0 ; i < result->N ; i++)
		v[i] = (double*) malloc(result->K*sizeof(double));

	for(unsigned long i = 0 ; i < result->N ; i++)
		for(unsigned long j = 0 ; j < result->K ; j++)
			v[i][j] = -log(1-result->alpha[i][j]);

	result->v = v;
}
