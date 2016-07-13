//Source: http://www.zentut.com/c-tutorial/c-quicksort-algorithm/
#include "knnclus.h"

namespace kNN
{

void Quicksort::swapLU(unsigned long *x, unsigned long *y)
{
    unsigned long temp;
    temp = *x;
    *x = *y;
    *y = temp;
}
 
void Quicksort::swapD(double *x, double*y)
{
    double temp;
    temp = *x;
    *x = *y;
    *y = temp;
}

long Quicksort::choose_pivot(long i, long j )
{
    return((i+j) /2);
}
 
void Quicksort::quicksort(double *list, unsigned long *indexes, long m, long n)
{
    long i,j,k;
	double key;
    if(m < n)
    {
        k = Quicksort::choose_pivot(m,n);
        Quicksort::swapD(&list[m],&list[k]);
		if(indexes != NULL) Quicksort::swapLU(&indexes[m], &indexes[k]);
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
                Quicksort::swapD(&list[i], &list[j]);
				if(indexes != NULL) Quicksort::swapLU(&indexes[i], &indexes[j]);
			}
        }
        /* swap two elements */
        swapD(&list[m], &list[j]);
		if(indexes != NULL) swapLU(&indexes[m], &indexes[j]);
 
        /* recursively sort the lesser list */
        Quicksort::quicksort(list, indexes, m, j-1);
        Quicksort::quicksort(list, indexes, j+1, n);
    }
}

} // NAMESPACE EkNN
