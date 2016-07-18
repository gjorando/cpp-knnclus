#include <knnclus.h>
#include <iostream>

#define N 6
#define D 2
#define K 3

int main(void)
{
	srand(time(NULL));

	/* 
	double *points = new double[D*N];
	
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
	
	kNNclus::Point *e = new kNNclus::Point[N];
	for(unsigned long i = 0 ; i < N ; i++)
	{
		e[i].setDepth(D);
		for(unsigned long j = 0 ; j < D ; j++)
			e[i][j+1] = points[i*D+j];
	}
	delete[] points;

	kNNclus::System<kNNclus::Point> sys(e, N, K);//*/

	unsigned int *h = new unsigned int[N];
	unsigned int *m = new unsigned int[N];
	unsigned int *s = new unsigned int[N];

	h[0] = 23;
	m[0] = 59;
	s[0] = 30;
	h[1] = 0;
	m[1] = 0;
	s[1] = 30;
	h[2] = 1;
	m[2] = 12;
	s[2] = 0;
	h[3] = 12;
	m[3] = 0;
	s[3] = 0;
	h[4] = 13;
	m[4] = 0;
	s[4] = 0;
	h[5] = 12;
	m[5] = 30;
	s[5] = 0;

	kNNclus::Hour *e = new kNNclus::Hour[N];
	for(int i = 0 ; i < N ; i++)
	{
		e[i].setHour(h[i]);
		e[i].setMinute(m[i]);
		e[i].setSecond(s[i]);
	}
	delete[] h;
	delete[] m;
	delete[] s;

	kNNclus::System<kNNclus::Hour> sys(e, N, K);

	sys.clusterize();
	std::cout << std::endl;
	sys.display();

	return 0;
}
