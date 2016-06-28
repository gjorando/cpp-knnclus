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
