/*! \file kNNclus_Utils.cpp
 *  \brief Implementations for kNNclus::Utils.
 *  \author LTI IUT Amiens
 */

#include "knnclus.h"

namespace kNNclus
{

void Utils::toss(unsigned long *a, unsigned long aSize, unsigned long iter)
{
	for(unsigned long i = 0 ; i < iter ; i++)
	{
		unsigned long r1 = rand()%aSize, r2 = rand()%aSize;
		unsigned long tmp = a[r1];
		a[r1] = a[r2];
		a[r2] = tmp;
	}
}

unsigned long *Utils::specialSort(double *s, unsigned long size)
{
	unsigned long *res = new unsigned long[size];
	for(unsigned long i = 0 ; i < size ; i++)
		res[i] = i;

	Quicksort::quicksort(s, res, 0, size-1);

	return res;
}

double Utils::median(double *t, unsigned long size)
{
	Quicksort::quicksort(t, NULL, 0, size-1);	
	return t[(size-1)/2];
}

} // NAMESPACE kNNclus
