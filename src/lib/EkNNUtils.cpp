#include "eknnclus.h"

void EkNNUtils::toss(unsigned long *a, unsigned long aSize, unsigned long iter)
{
	for(unsigned long i = 0 ; i < iter ; i++)
	{
		unsigned long r1 = rand()%aSize, r2 = rand()%aSize;
		unsigned long tmp = a[r1];
		a[r1] = a[r2];
		a[r2] = tmp;
	}
}

unsigned long *EkNNUtils::specialSort(double *s, unsigned long size)
{
	unsigned long *res = new unsigned long[size];
	for(unsigned long i = 0 ; i < size ; i++)
		res[i] = i;

	EkNNQuicksort::quicksort(s, res, 0, size-1);

	return res;
}

double EkNNUtils::median(double *t, unsigned long size)
{
	EkNNQuicksort::quicksort(t, NULL, 0, size-1);	
	return t[(size-1)/2];
}
