#include <knnclus.h>
#include <iostream>

#define N 6
#define D 2
#define K 3

int main(void)
{
	srand(time(NULL));

	double *points = new double[D*N];
	//for(int i = 0 ; i < D*N ; i++)
	//	points[i] = i;
	
	points[0] = 0;
	points[1] = 9;
	points[2] = 4;
	points[3] = 1;
	points[4] = 7;
	points[5] = -7;
	points[6] = -4;
	points[7] = -4;
	points[8] = -1;
	points[9] = 0;
	points[10] = 6;
	points[11] = 5;

	kNNclus::System s(points, D, N, K);

	s.clusterize();
	s.display();

	return 0;
}
