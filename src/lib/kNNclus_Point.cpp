#include "knnclus.h"

namespace kNNclus
{

Point::Point(): AbstractClusterElement()
{
	coordinates = NULL;
	D = 0;
}

Point::Point(unsigned long dim): AbstractClusterElement()
{
	coordinates = new double[dim];
	D = dim;
}

Point::Point(Point &p): AbstractClusterElement()
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

void Point::setDepth(unsigned long d)
{
	D = d;
	if(coordinates != NULL) delete coordinates;
	coordinates = new double[d];
}

double Point::dissimilarity(AbstractClusterElement &e)
{
	try
	{
		Point &p = dynamic_cast<Point&>(e);
		bool smallestDimIsThis = D<p.depth()?true:false;
		double smallestDim = smallestDimIsThis?D:p.depth();
		double calc = 0;
		for(unsigned long i = 0 ; i < smallestDim ; i++)
			calc += (coordinates[i] - p[i+1])*(coordinates[i] - p[i+1]);

		return sqrt(calc);
	}
	catch (const std::bad_cast &e)
	{
		std::cerr << e.what() << std::endl;
		std::cerr << &e << " isn't of type Point" << std::endl;

		return -1;
	}
}

std::string Point::toString()
{
	std::ostringstream stream;
	for(unsigned long j = 0 ; j < D ; j++)
		stream << coordinates[j] << ((j+1!=D)?":":"");
	stream << " | #" << cluster;

	return stream.str();
}

} // NAMESPACE kNNclus
