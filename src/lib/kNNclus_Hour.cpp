/*! \file kNNclus_Hour.cpp
 *  \brief Implementations for kNNclus::Hour.
 *  \author LTI IUT Amiens
 */

#include "knnclus.h"

namespace kNNclus
{

Hour::Hour(): Hour(0, 0, 0)
{
}

Hour::Hour(unsigned int h, unsigned int m, unsigned int s): AbstractClusterElement()
{
	setHour(h);
	setMinute(m);
	setSecond(s);
}

double Hour::dissimilarity(AbstractClusterElement &e)
{
	try
	{
		Hour &h = dynamic_cast<Hour&>(e);
		
		double thisDec = asDecimal(),
			   otherDec = h.asDecimal();

		double *m = (thisDec<otherDec)?&thisDec:&otherDec;
		double *M = (thisDec<otherDec)?&otherDec:&thisDec;

		double case1 = (*M)-(*m),
			   case2 = (24+(*m))-(*M);

		return (case1<case2)?case1:case2;
	}
	catch (const std::bad_cast &e)
	{
		std::cerr << e.what() << std::endl;
		std::cerr << &e << " isn't of type Hour" << std::endl;

		return -1;
	}
}

std::string Hour::toString()
{
	std::ostringstream stream;
	stream << hour << ":" << minute << ":" << second << " | #" << cluster;
	return stream.str();
}

unsigned int Hour::getHour()
{
	return hour;
}

void Hour::setHour(unsigned int h)
{
	hour = h;
	if(hour >= 24)
		hour%= 24;
}

unsigned int Hour::getMinute()
{
	return minute;
}

void Hour::setMinute(unsigned int m)
{
	minute = m;
	if(minute >= 60)
	{
		minute%=60;
		setHour(hour+(m/60));
	}
}

unsigned int Hour::getSecond()
{
	return second;
}

void Hour::setSecond(unsigned int s)
{
	second = s;
	if(second >= 60)
	{
		second%=60;
		setMinute(minute+(s/60));
	}
}

double Hour::asDecimal()
{
	return hour+((double)minute/60)+((double)second/3600);
}

}
