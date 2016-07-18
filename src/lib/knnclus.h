/*! \file knnclus.h
 *  \brief Definitions for the kNNclus module.
 *  \author LTI IUT Amiens
 */

#ifndef _KNNCLUS_KNNCLUS_H_
#define _KNNCLUS_KNNCLUS_H_

#include <iostream>
#include <typeinfo>
#include <cstdlib>
#include <string>
#include <sstream>
#include <cmath>

/*! \brief Global namespace.
 *
 *  This namespace contains all the classes and methods of the library.
 */
namespace kNNclus
{

// CLASS DEFINITIONS

/*! \brief Abstract container for an object which can be clusterized.
 *
 *  Stores the label of the cluster and defines a method which returns the dissimilarity between the element and another element. You can make child classes based on this one and implement the way the dissimilarity is calculated. kNNclus::Point is an exemple of cluster element describing a point in a N-dimensionnal euclidian space, whose dissimilarity corresponds to the euclidian distance.
 */
class AbstractClusterElement
{
protected:
	
	unsigned long cluster; //!< Label for the cluster of the element.

public:

	/*! \brief Empty constructor for an AbstractClusterElement.
	 */
	AbstractClusterElement();
	/*! \brief Returns the dissimilarity between this element and another element.
	 *  \param e The other element.
	 *  \return A real describing the dissimilarity.
	 */
	virtual double dissimilarity(AbstractClusterElement &e) = 0;
	/*! \brief Returns the display string of the element.
	 *  \return A string describing the element.
	 */
	virtual std::string toString() = 0;
	/*! \brief Getter of cluster.
	 *  \return cluster.
	 */
	unsigned long getCluster();
	/*! \brief Setter of cluster.
	 *  \param c new value for cluster.
	 */
	void setCluster(unsigned long c);
};

/*! \brief Container of a hour.
 *
 *  Stores the value of a hour to clusterize them.
 */
class Hour: public AbstractClusterElement
{
private:
	
	unsigned int hour, //!< Value of the hour.
				 minute, //!< Value of the minute.
				 second; //!< Value of the second.

public:

	/*! \brief Empty constructor for a clusterizable hour.
	 */
	Hour();
	/*! \brief Default constructor for a clusterizable hour.
	 *  \param h The hour.
	 *  \param m The minute.
	 *  \param s The second.
	 */
	Hour(unsigned int h, unsigned int m, unsigned int s);
	/*! \brief Get the distance on a 24h clock between a hour and another one.
	 *  \param e The other element
	 */
	double dissimilarity(AbstractClusterElement &e);
	std::string toString();
	/*! \brief Getter of hour.
	 *  \return Value of hour.
	 */
	unsigned int getHour();
	/*! \brief Setter of hour.
	 *  \param h New value of hour.
	 */
	void setHour(unsigned int h);
	/*! \brief Getter of minute.
	 *  \return Value of minute.
	 */
	unsigned int getMinute();
	/*! \brief Setter of minute.
	 *  \param m New value of minute.
	 */
	void setMinute(unsigned int m);
	/*! \brief Getter of second.
	 *  \return Value of second.
	 */
	unsigned int getSecond();
	/*! \brief Setter of second.
	 *  \param s New value of second.
	 */
	void setSecond(unsigned int s);
	/*! \brief Converts the hour to a decimal value.
	 *  \return Decimal value.
	 */
	double asDecimal();
};

/*! \brief Container of a two dimensional point.
 *
 *  Stores the coordinates of a point as well as the label of its cluster.
 */
class Point: public AbstractClusterElement
{
private:

	double *coordinates; //!< Coordinates for the point.
	unsigned long D; //!< Number of dimensions.

public:

	/*! \brief Empty constructor for the Point.
	 */
	Point();
	/*! \brief Constructor for the Point.
	 *  \param dim Number of dimensions.
	 */
	Point(unsigned long dim);
	/*! \brief Copy constructor.
	 *  \param p Point to copy.
	 */
	Point(Point &p);
	/*! \brief Destructor of Point.
	 */
	~Point();
	/*! \brief Gets the coordinate of a given dimension (can be read or written).
	 *  \param i Dimension. If i > D or i <= 0, result may be indeterminated.
	 *  \return A reference to the coordinate at dimension i.
	 */
	double &operator[](size_t i);
	/*! \brief Getter of D.
	 *  \return D.
	 */
	unsigned long depth();
	/*! \brief Changes the depth of an Point.
	 *  \param d New value for D.
	 *
	 *  Be careful, this method erases your coordinates.
	 */
	void setDepth(unsigned long d);
	/*! \brief Computes the euclidian distance between two Points.
	 *  \param e The point.
	 *  \return Euclidian distance between this and p.
	 */
	double dissimilarity(AbstractClusterElement &e);
	std::string toString();
};

template <typename E = AbstractClusterElement>
/*! \brief Container of an EkNN two dimensional system.
 *
 *  Stores the datas of an EkNN two dimensional system. Must be initialized with EkNNInit(double **points, long K).
 */
class System
{
private:

	E *elements; //!< The points of the system.
	double **distances; //!< N*N array storing the euclidian distances for each point (useful to compute kNN).
	double **alpha; //!< N*K alpha_ik matrix (useful to compute v).
	double **v; //!< N*K v_ik matrix.
	unsigned long **kNN; //!< N*K array storing the K nearest neighbours for each point.
	double gamma; //!< The gamma parameter (useful to compute alpha).
	unsigned long N; //!< Number of points.
	unsigned long K; //!< K parameter for the kNN.
	unsigned long C; //!< Actual number of clusters.

	/*! \brief Computes initial clusters of an System.
	 *
	 *  Randomly inits one cluster per point, and one point per cluster.
	 */
	void initClusters();
	/*! \brief Computes euclidian distances between each point of an System.
	 *
	 *  It fulls the distance attribute of an System with proper distances.
	 */
	void initDistances();
	/*! \brief Computes the kNN algorithm of an System.
	 *
	 *  Determines which are the K nearest neighbours for each point, and puts the result in the kNN attribute of the System.
	 */
	void initKNN();
	/*! \brief Computes the gamma of an System.
	 *
	 *  This parameter is essential to compute the alpha matrix, if you want to call EkNNInitAlpha(System*), please call this function first!
	 */
	void initGamma();
	/*! \brief Computes the alpha_ik matrix of an System.
	 *
	 *  This matrix is essential to compute the v matrix, if you want to call EkNNInitV(System*), please call this function first!
	 */
	void initAlpha();
	/*! \brief Computes a special v_ik of an System.
	 *
	 *  This is a modified version of the original v_ij square matrix used in the original EkNNclus algorithm. Instead of a square matrix of N*N points, we actually only need a v_ik matrix.
	 */
	void initV();
	/*! \brief Updates the actual number of clusters C in an System and refreshes the labels of the clusters in points.
	 */
	void updateC();

public:

	/*! \brief Constructor of System.
	 *  \param elems Array of N*D values (D first values for the first point, D next ones for the second point, and so on).
	 *  \param n Number of points.
	 *  \param k K parameter for the kNN algorithm.
	 *
	 *  When you want to clusterize a set of points, you need essential parameters: this constructor computes them.
	 */
	System(E *elems, unsigned long n, unsigned long k);
	/*! \brief Destructor of System.
	 */
	~System();
	/*! \brief Executes the EkNNclus procedure.
     *
	 *  This is the main function: once you've properly initialized an System, use this function to group the points in clusters using the EkNNclus algorithm as described in "Ek-NNclus: a clustering procedure based on the evidential K-nearest neighbor rule" by Thierry Denoeux, Orakanya Kanjanatarakul and Songsak Sriboonchitta. In this function, we don't compute the evidential part of the algorithm.
	 */
	void clusterize();
	/*! \brief Exports the points to CSV.
	 *  \param path the path of export.
	 *
	 *  Exports the coordinates of the points and the clusters in a csv file. If we got a 2D system, the first line is dedicated to the eastings, whereas each next line corresponds to the northings of a cluster (the first cell of each line stores the label of the cluster). Doesn't work yet for n-dimensional systems.
	 */
	void exportToCSV(std::string path);
	/*! \brief Debugging function that displays on standard output the datas of the system.
	 */
	void display();
};

/*! \brief Some static methods.
 *
 *  This class contains some static utilitary functions.
 */
class Utils
{
public:
	
	/*! \brief Tosses an array a iter times.
	 *  \param a The array to toss.
	 *  \param aSize Size of a.
	 *  \param iter number of random swaps to do.
	 */
	static void toss(unsigned long *a, unsigned long aSize, unsigned long iter);
	/*! \brief Sorts an array and returns the sorted indexes.
	 *  \param s The array to sort.
	 *  \param size Size of s.
	 *  \return The sorted indexes.
	 */
	static unsigned long *specialSort(double *s, unsigned long size);
	/*! \brief Computes the median value of an array.
	 *  \param t Array to compute.
 	 *  \param size Size of t.
	 *  \return The median value of t.
	 */
	static double median(double *t, unsigned long size);
};

/*! \brief Methods for quicksort algorithm.
 */
class Quicksort
{
private:
	
	/*! \brief Swaps in memory two unsigned long.
	 *  \param x Pointer to the first unsigned long.
	 *  \param y Pointer to the second unsigned long.
	 */
	static void swapLU(unsigned long *x, unsigned long *y);
	/*! \brief Swaps in memory two double.
	 *  \param x Pointer to the first double.
	 *  \param y Pointer to the second double.
	 */
	static void swapD(double *x, double*y);
	/*! \brief Determines a pivot for the quicksort algorithm.
	 *  \param i Min value.
	 *  \param j Max value.
	 *  \return A pivot.
	 *
	 *  The implementation in quicksort.c uses the mean of i and j as a pivot.
	 */
	static long choose_pivot(long i, long j);

public:

	/*! \brief Sorts a list using quicksort algorithm.
	 *  \param list The array to sort.
	 *  \param indexes Another array that will go through the same swap operations as the list parameter. Just use the NULL pointer if you don't care.
	 *  \param m Min value.
	 *  \param n Max value.
	 *  
	 *  This variant of an implementation of the quicksort of algorithm (as found on: http://www.zentut.com/c-tutorial/c-quicksort-algorithm/ ) performs the same swaps on both list and indexes, but sorting list: it can be useful in specific cases, for example when you need to keep the initial positions of the elements in the list.
	 */
	static void quicksort(double *list, unsigned long *indexes, long m, long n);
};

//TEMPLATE CLASS IMPLEMENTATION

//System

template <typename E>
System<E>::System(E *elems, unsigned long n, unsigned long k)
{	
	N = n;
	K = k;
	C = n;

	elements = elems;
	initClusters();
	initDistances();
	initKNN();
	initGamma();
	initAlpha();
	initV();
}

template <typename E>
void System<E>::initClusters()
{
	unsigned long *clus = new unsigned long[N];

	for(unsigned long i = 0 ; i < N ; i++)
		clus[i] = i+1;

	Utils::toss(clus, N, 1.5*N);

	for(unsigned long i = 0 ; i < N ; i++)
		elements[i].setCluster(clus[i]);

	delete[] clus;
}

template <typename E>
void System<E>::initDistances()
{
	double **dist = new double*[N];
	for(unsigned long i = 0 ; i < N ; i++)
		dist[i] = new double[N];

	for(unsigned long i = 0 ; i < N ; i++)
	{
		dist[i][i] = 0;
		for(unsigned long j = 0 ; j < i ; j++)
		{
			dist[i][j] = elements[i].dissimilarity(elements[j]);
			dist[j][i] = dist[i][j];
		}
	}

	distances = dist;
}

template <typename E>
void System<E>::initKNN()
{
	unsigned long **knn = new unsigned long*[N];
	for(unsigned long i = 0 ; i < N ; i++)
		knn[i] = new unsigned long[K];

	for(unsigned long i = 0 ; i < N ; i++)
	{
		double *tmpD = new double[N];

		for(unsigned long j = 0 ; j < N ; j++)
			tmpD[j] = distances[i][j];

		unsigned long *tmp = Utils::specialSort(tmpD, N);
		
		unsigned long j = 0, k = 0; 
		while(j < K)
		{
			if(tmpD[k] != 0)
			{
				knn[i][j] = tmp[k];
				j++;
			}
			k++;
		}

		delete[] tmpD;
		delete[] tmp;
	}

	kNN = knn;
}

template <typename E>
void System<E>::initGamma()
{
	double *dist;
	dist = new double[K*N];

	unsigned long cpt = 0;

	for(unsigned long i = 0 ; i < N ; i++)
		for(unsigned long j = 0 ; j < K ; j++)
			dist[cpt++] = distances[i][kNN[i][j]];

	gamma = 1/Utils::median(dist, K*N);

	delete[] dist;

}

template <typename E>
void System<E>::initAlpha()
{
	double **a = new double*[N];
	for(unsigned long i = 0 ; i < N ; i++)
		a[i] = new double[K];

	for(unsigned long i = 0 ; i < N ; i++)
		for(unsigned long j = 0 ; j < K ; j++)
			a[i][j] = exp(-gamma*distances[i][kNN[i][j]]*distances[i][kNN[i][j]]);

	alpha = a;
}

template <typename E>
void System<E>::initV()
{
	v = new double*[N];
	for(unsigned long i = 0 ; i < N ; i++)
		v[i] = new double[K];

	for(unsigned long i = 0 ; i < N ; i++)
		for(unsigned long j = 0 ; j < K ; j++)
			v[i][j] = -log(1-alpha[i][j]);
}

template <typename E>
System<E>::~System()
{
	delete[] elements;
	for(unsigned long i = 0 ; i < N ; i++)
	{
		delete[] distances[i];
		delete[] kNN[i];
		delete[] alpha[i];
		delete[] v[i];
	}
	delete[] distances;
	delete[] kNN;
	delete[] alpha;
	delete[] v;
}

template <typename E>
void System<E>::clusterize()
{
	bool flag = true;
	unsigned long *sigma = new unsigned long[N];
	for(unsigned long i = 0 ; i < N ; i++)
		sigma[i] = i;

	unsigned long iter = 1;

	while(flag)
	{
		std::cout << "Iteration #" << iter << std::endl;

		flag = false;

		double **u = new double*[N];
		for(unsigned long i = 0 ; i < N ; i++)
		{
			u[i] = new double[C];
			for(unsigned long j = 0 ; j < C ; j++)
				u[i][j] = 0;
		}
		
		Utils::toss(sigma, N, 2*N);

		for(unsigned long i = 0 ; i < N ; i++)
		{
			std::cout << sigma[i] << "... ";

			double max = 0;
			unsigned long kstar = 1;

			for(unsigned long k = 0 ; k < C ; k++)
			{
				for(unsigned long j = 0 ; j < K ; j++)
					if(elements[kNN[sigma[i]][j]].getCluster() == k+1)
						u[sigma[i]][k]+= v[sigma[i]][j];

				if(u[sigma[i]][k] >= max)
				{
					max = u[sigma[i]][k];
					kstar = k+1;
				}
			}

			if(elements[sigma[i]].getCluster() != kstar)
			{
				elements[sigma[i]].setCluster(kstar);
				flag = true;
			}
		}
		updateC();
		for(unsigned long i = 0 ; i < N ; i++)
			delete[] u[i];
		delete u;
	
		if(C == 1)
		{
			std::cerr << "clusterize: Gave only one cluster, please try again" << std::endl;
			exit(1);
		}

		std::cout << std::endl;
		iter++;
	}

	delete[] sigma;

}

template <typename E>
void System<E>::updateC()
{
	unsigned long *clus = new unsigned long[N];
	for(unsigned long i = 0 ; i < N ; i++)
		clus[i] = elements[i].getCluster();

	Quicksort::quicksort((double*)clus, NULL, 0, N-1);

	//We kept C allocations because we need to use realloc
	unsigned long *distClus = (unsigned long*) malloc(sizeof(unsigned long));
	distClus[0] = clus[0];
	unsigned long c = 1;

	for(unsigned long i = 1 ; i < N ; i++)
		if(clus[i] != clus[i-1])
		{
			c++;
			distClus = (unsigned long*) realloc(distClus, c*sizeof(unsigned long));
			distClus[c-1] = clus[i];
		}

	for(unsigned long i = 0 ; i < N ; i++)
	{
		unsigned long oldClus = elements[i].getCluster();
		unsigned long j = 0;
		while(oldClus!=distClus[j])
		{	
			j++;
			if(j>=c)
			{
				std::cerr << "EkNNUpdateC: Unexpected error" << std::endl;
				exit(2);
			}
		}
		elements[i].setCluster(j+1);
	}

	C = c;

	delete[] clus;
	free(distClus);

}

template <typename E>
void System<E>::display()
{
	std::cout << "N=" << N << std::endl;
	std::cout << "K=" << K << std::endl;
	std::cout << "C=" << C << std::endl;

	std::cout << std::endl << "elements=" << std::endl;
	for(unsigned long i = 0 ; i < N ; i++)
		std::cout << elements[i].toString() << std::endl;
	
	std::cout << std::endl << "distances=" << std::endl;
	for(unsigned long i = 0 ; i < N ; i++)
	{
		for(unsigned long j = 0 ; j < N ; j++)
			std::cout << distances[i][j] << " ";
		std::cout << std::endl;
	}

	std::cout << std::endl << "kNN=" << std::endl;
	for(unsigned long i = 0 ; i < N ; i++)
	{
		for(unsigned long j = 0 ; j < K ; j++)
			std::cout << kNN[i][j] << " ";
		std::cout << std::endl;
	}

	std::cout << std::endl << "gamma=" << std::endl << gamma <<std::endl;

	std::cout << std::endl << "alpha=" << std::endl;
	for(unsigned long i = 0 ; i < N ; i++)
	{
		for(unsigned long j = 0 ; j < K ; j++)
			std::cout << alpha[i][j] << " ";
		std::cout << std::endl;
	}

	std::cout << std::endl << "v=" << std::endl;
	for(unsigned long i = 0 ; i < N ; i++)
	{
		for(unsigned long j = 0 ; j < K ; j++)
			std::cout << v[i][j] << " ";
		std::cout << std::endl;
	}
}

} // NAMESPACE kNNclus

#endif // _KNNCLUS_KNNCLUS_H_
