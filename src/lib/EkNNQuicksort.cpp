//Source: http://www.zentut.com/c-tutorial/c-quicksort-algorithm/
#include "eknnclus.h"

void EkNNQuicksort::swapLU(unsigned long *x, unsigned long *y)
{
    unsigned long temp;
    temp = *x;
    *x = *y;
    *y = temp;
}
 
void EkNNQuicksort::swapD(double *x, double*y)
{
    double temp;
    temp = *x;
    *x = *y;
    *y = temp;
}

long EkNNQuicksort::choose_pivot(long i, long j )
{
    return((i+j) /2);
}
 
void EkNNQuicksort::quicksort(double *list, unsigned long *indexes, long m, long n)
{
    long i,j,k;
	double key;
    if(m < n)
    {
        k = EkNNQuicksort::choose_pivot(m,n);
        EkNNQuicksort::swapD(&list[m],&list[k]);
		if(indexes != NULL) EkNNQuicksort::swapLU(&indexes[m], &indexes[k]);
        key = list[m];
        i = m+1;
        j = n;
        while(i <= j)
        {
            while((i <= n) && (list[i] <= key))
                i++;
            while((j >= m) && (list[j] > key))
                j--;
            if(i < j)
			{
                EkNNQuicksort::swapD(&list[i], &list[j]);
				if(indexes != NULL) EkNNQuicksort::swapLU(&indexes[i], &indexes[j]);
			}
        }
        /* swap two elements */
        swapD(&list[m], &list[j]);
		if(indexes != NULL) swapLU(&indexes[m], &indexes[j]);
 
        /* recursively sort the lesser list */
        EkNNQuicksort::quicksort(list, indexes, m, j-1);
        EkNNQuicksort::quicksort(list, indexes, j+1, n);
    }
}
