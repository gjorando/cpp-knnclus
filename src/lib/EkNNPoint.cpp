#include "eknnclus.h"

EkNNPoint::EkNNPoint()
{
	coordinates = NULL;
	D = 0;
}

EkNNPoint::EkNNPoint(unsigned long dim)
{
	coordinates = new double[dim];
	D = dim;
}

EkNNPoint::EkNNPoint(EkNNPoint &p)
{
	coordinates = new double[p.depth()];
	D = p.depth();
	cluster = p.getCluster();

	for(unsigned long i = 1 ; i <= D ; i++)
		coordinates[i-1] = p[i];
}

EkNNPoint::~EkNNPoint()
{
	delete coordinates;
}

double &EkNNPoint::operator[](size_t i)
{
	if((i <= D) && (i > 0))
		return coordinates[i-1];
	else
		return coordinates[0];
}

unsigned long EkNNPoint::depth()
{
	return D;
}

unsigned long EkNNPoint::getCluster()
{
	return cluster;
}

void EkNNPoint::setCluster(unsigned long c)
{
	cluster = c;
}

void EkNNPoint::setDepth(unsigned long d)
{
	D = d;
	if(coordinates != NULL) delete coordinates;
	coordinates = new double[d];
}

double EkNNPoint::distance(EkNNPoint &p)
{
	bool smallestDimIsThis = D<p.depth()?true:false;
	double smallestDim = smallestDimIsThis?D:p.depth();
	double calc = 0;
	for(unsigned long i = 0 ; i < smallestDim ; i++)
		calc += (coordinates[i] - p[i+1])*(coordinates[i] - p[i+1]);

	return sqrt(calc);
}
