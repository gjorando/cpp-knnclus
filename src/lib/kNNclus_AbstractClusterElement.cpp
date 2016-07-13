/*! \file kNNclus_AbstractClusterElement.cpp
 *  \brief Implementations for kNNclus::AbstractClusterElement.
 *  \author LTI IUT Amiens
 */

#include "knnclus.h"

namespace kNNclus
{

AbstractClusterElement::AbstractClusterElement()
{
	cluster = 0;
}

unsigned long AbstractClusterElement::getCluster()
{
	return cluster;
}

void AbstractClusterElement::setCluster(unsigned long c)
{
	cluster = c;
}

}
