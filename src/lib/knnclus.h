/*! \file knnwindev.h
 *  \brief Definitions for the kNNclus module.
 *  \author LTI IUT Amiens
 */

#ifndef _KNNCLUS_KNNCLUS_H_
#define _KNNCLUS_KNNCLUS_H_

#include <iostream>
#include <cstdlib>
#include <string>
#include <cmath>

namespace kNN
{

// CLASS DEFINITIONS

/*! \brief Container of a two dimensional point.
 *
 *  Stores the coordinates of a point as well as the label of its cluster.
 */
class Point
{
private:

	double *coordinates; //!< Coordinates for the point
	unsigned long D; //!< Number of dimensions
	unsigned long cluster; //!< Label for the cluster of the point.

public:

	/*! \brief Empty constructor for the Point
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
	/*! \brief Getter of cluster.
	 *  \return cluster.
	 */
	unsigned long getCluster();
	/*! \brief Setter of cluster.
	 *  \param c new value for cluster.
	 */
	void setCluster(unsigned long c);
	/*! \brief Changes the depth of an Point.
	 *  \param d New value for D.
	 *
	 *  Be careful, this method erases your coordinates.
	 */
	void setDepth(unsigned long d);
	/*! \brief Computes the euclidian distance between two Points.
	 *  \param p1 The point.
	 *  \return Euclidian distance between this and p.
	 */
	double distance(Point &p);
};

/*! \brief Container of an EkNN two dimensional system.
 *
 *  Stores the datas of an EkNN two dimensional system. Must be initialized with EkNNInit(double **points, long K).
 */
class System
{
private:

	Point *points; //!< The points of the system.
	double **distances; //!< N*N array storing the euclidian distances for each point (useful to compute kNN).
	double **alpha; //!< N*K alpha_ik matrix (useful to compute v).
	double **v; //!< N*K v_ik matrix.
	unsigned long **kNN; //!< N*K array storing the K nearest neighbours for each point.
	double gamma; //!< The gamma parameter (useful to compute alpha).
	unsigned long N; //!< Number of points.
	unsigned long K; //!< K parameter for the kNN.
	unsigned long C; //!< Actual number of clusters.
	unsigned long D; //!< Depth of the system.

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
	 *  \param p array of N*D values (D first values for the first point, D next ones for the second point, and so on).
	 *  \param n number of points.
	 *  \param k K parameter for the kNN algorithm.
	 *
	 *  When you want to clusterize a set of points, you need essential parameters: this constructor computes them.
	 */
	System(double *p, unsigned long d, unsigned long n, unsigned long k);
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
public:
	
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

} // NAMESPACE kNN

#endif // _KNNCLUS_KNNCLUS_H_
