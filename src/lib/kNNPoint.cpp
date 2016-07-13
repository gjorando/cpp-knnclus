#include "knnclus.h"

namespace kNN
{

Point::Point()
{
	coordinates = NULL;
	D = 0;
}

Point::Point(unsigned long dim)
{
	coordinates = new double[dim];
	D = dim;
}

Point::Point(Point &p)
{
	coordinates = new double[p.depth()];
	D = p.depth();
	cluster = p.getCluster();

	for(unsigned long i = 1 ; i <= D ; i++)
		coordinates[i-1] = p[i];
}

Point::~Point()
{
	delete coordinates;
}

double &Point::operator[](size_t i)
{
	if((i <= D) && (i > 0))
		return coordinates[i-1];
	else
		return coordinates[0];
}

unsigned long Point::depth()
{
	return D;
}

unsigned long Point::getCluster()
{
	return cluster;
}

void Point::setCluster(unsigned long c)
{
	cluster = c;
}

void Point::setDepth(unsigned long d)
{
	D = d;
	if(coordinates != NULL) delete coordinates;
	coordinates = new double[d];
}

double Point::distance(Point &p)
{
	bool smallestDimIsThis = D<p.depth()?true:false;
	double smallestDim = smallestDimIsThis?D:p.depth();
	double calc = 0;
	for(unsigned long i = 0 ; i < smallestDim ; i++)
		calc += (coordinates[i] - p[i+1])*(coordinates[i] - p[i+1]);

	return sqrt(calc);
}

} // NAMESPACE EkNN
