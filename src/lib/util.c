#include "eknnwindev.h"
#include "quicksort.c"

void toss(unsigned long *a, unsigned long aSize, unsigned long iter)
{
	for(unsigned long i = 0 ; i < iter ; i++)
	{
		unsigned long r1 = rand()%aSize, r2 = rand()%aSize;
		unsigned long tmp = a[r1];
		a[r1] = a[r2];
		a[r2] = tmp;
	}
}

double distance(EkNNPoint p1, EkNNPoint p2)
{
	return sqrt((p2.x-p1.x)*(p2.x-p1.x)+(p2.y-p1.y)*(p2.y-p1.y));
}

unsigned long *specialSort(double *s, unsigned long size)
{
	unsigned long *res = (unsigned long*) malloc(size*sizeof(unsigned long));
	for(unsigned long i = 0 ; i < size ; i++)
		res[i] = i;

	quicksort(s, res, 0, size-1);

	return res;
}

double median(double *t, unsigned long size)
{
	quicksort(t, NULL, 0, size-1);	
	return t[(size-1)/2];
}

void EkNNUpdateC(EkNNSystem *s)
{
	unsigned long *clus = (unsigned long*) malloc(s->N*sizeof(unsigned long));
	for(unsigned long i = 0 ; i < s->N ; i++)
		clus[i] = s->points[i].cluster;

	quicksort((double*)clus, NULL, 0, s->N-1);

	unsigned long *distClus = (unsigned long*) malloc(sizeof(unsigned long));
	distClus[0] = clus[0];
	unsigned long c = 1;

	for(unsigned long i = 1 ; i < s->N ; i++)
		if(clus[i] != clus[i-1])
		{
			c++;
			distClus = (unsigned long*) realloc(distClus, c*sizeof(unsigned long));
			distClus[c-1] = clus[i];
		}

	for(unsigned long i = 0 ; i < s->N ; i++)
	{
		unsigned long oldClus = s->points[i].cluster;
		unsigned long j = 0;
		while(oldClus!=distClus[j])
		{	
			j++;
			if(j>=c)
			{
				fprintf(stderr, "EkNNUpdateC: Unexpected error\n");
				exit(2);
			}
		}
		s->points[i].cluster = j+1;
	}

	s->C = c;

	free(clus);
	free(distClus);
	//TODO : must update the size of C, and change the labels of the clusters to fit from 1 to C
}
