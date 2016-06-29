/*! \file eknnwindev.h
 *  \brief Functions and structures definitions for the EkNNWindev module.
 *  \author LTI IUT Amiens
 */

#ifndef _EKNNWINDEV_EKNNWINDEV_H_
#define _EKNNWINDEV_EKNNWINDEV_H_

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// MACRO DEFINITIONS

#define bool int
#define TRUE 1
#define FALSE 0

// STRUCTURE DEFINITIONS

/*! \brief Container of a two dimensional point.
 *
 *  Stores the coordinates of a point as well as the label of its cluster.
 */
struct EkNNPoint
{
	double x; //!< Easting of the point.
	double y; //!< Northing of the point.
	unsigned long cluster; //!< Label for the cluster of the point.
};

typedef struct EkNNPoint EkNNPoint; //!< Alias for the struct EkNNPoint.

/*! \brief Container of an EkNN two dimensional system.
 *
 *  Stores the datas of an EkNN two dimensional system. Must be initialized with EkNNInit(double **points, long K).
 */
struct EkNNSystem
{
	EkNNPoint *points; //!< The points of the system.
	double **distances; //!< N*N array storing the euclidian distances for each point (useful to compute kNN).
	double **alpha; //!< N*K alpha_ik matrix (useful to compute v).
	double **v; //!< N*K v_ik matrix.
	unsigned long **kNN; //!< N*K array storing the K nearest neighbours for each point.
	double gamma; //!< The gamma parameter (useful to compute alpha).
	unsigned long N; //!< Number of points.
	unsigned long K; //!< K parameter for the kNN.
	unsigned long C; //!< Actual number of clusters.
};

typedef struct EkNNSystem EkNNSystem; //!< Alias for the struct EkNNSystem.

// FUNCTION DEFINITIONS

// init.c

/*! \brief Computes essential datas needed in EkNNclus procedure.
 *  \param points 2D array of N lines and 2 columns (x and y).
 *  \param N number of points.
 *  \param K K parameter for the kNN algorithm.
 *  \return A pointer to the newly created EkNNSystem.
 *
 *  When you want to clusterize a set of points, you must first init an EkNNSystem using this function.
 */
EkNNSystem *EkNNInit(double **points, unsigned long N, unsigned long K);
/*! \brief Deallocates an EkNNSystem.
 *  \param s A pointer to the EkNNSystem to delete.
 *
 *  When you're done with your EkNNSystem, you can use this function to safely deallocate the memory.
 */
void EkNNDestroy(EkNNSystem *s);
/*! \brief Computes initial clusters of an EkNNSystem.
 *  \param result the EkNNSystem.
 *
 *  Randomly inits one cluster per point, and one point per cluster.
 *  BE CAREFUL WITH THIS FUNCTION, IT SHOULDN'T BE CALLED OUTSIDE OF EkNNInit(double **, unsigned long, unsigned long)!
 */
void EkNNInitClusters(EkNNSystem *result);
/*! \brief Computes euclidian distances between each point of an EkNNSystem.
 *  \param result the EkNNSystem.
 *
 *  It fulls the distance attribute of an EkNNSystem with proper distances.
 *  BE CAREFUL WITH THIS FUNCTION, IT SHOULDN'T BE CALLED OUTSIDE OF EkNNInit(double **, unsigned long, unsigned long)!
 */
void EkNNInitDistances(EkNNSystem *result);
/*! \brief Computes the kNN algorithm of an EkNNSystem.
 *  \param result the EkNNSystem.
 *
 *  Determines which are the K nearest neighbours for each point, and puts the result in the kNN attribute of the EkNNSystem.
 *  BE CAREFUL WITH THIS FUNCTION, IT SHOULDN'T BE CALLED OUTSIDE OF EkNNInit(double **, unsigned long, unsigned long)!
 */
void EkNNInitKNN(EkNNSystem *result);
/*! \brief Computes the gamma of an EkNNSystem.
 *  \param result the EkNNSystem.
 *
 *  This parameter is essential to compute the alpha matrix, if you want to call EkNNInitAlpha(EkNNSystem*), please call this function first!
 *  BE CAREFUL WITH THIS FUNCTION, IT SHOULDN'T BE CALLED OUTSIDE OF EkNNInit(double **, unsigned long, unsigned long)!
 */
void EkNNInitGamma(EkNNSystem *result);
/*! \brief Computes the alpha_ik matrix of an EkNNSystem.
 *  \param result the EkNNSystem.
 *
 *  This matrix is essential to compute the v matrix, if you want to call EkNNInitV(EkNNSystem*), please call this function first!
 *  BE CAREFUL WITH THIS FUNCTION, IT SHOULDN'T BE CALLED OUTSIDE OF EkNNInit(double **, unsigned long, unsigned long)!
 */
void EkNNInitAlpha(EkNNSystem *result);
/*! \brief Computes a special v_ik of an EkNNSystem.
 *  \param result the EkNNSystem.
 *
 *  This is a modified version of the original v_ij square matrix used in the original EkNNclus algorithm. Instead of a square matrix of N*N points, we actually only need a v_ik matrix.
 *  BE CAREFUL WITH THIS FUNCTION, IT SHOULDN'T BE CALLED OUTSIDE OF EkNNInit(double **, unsigned long, unsigned long)!
 */
void EkNNInitV(EkNNSystem *result);

//general.c

/*! \brief Displays all the attributes of an EkNNSystem.
 *  \param foo the EkNNSystem.
 */
void EkNNDisplay(EkNNSystem *foo);
/*! \brief Executes the EkNNclus procedure.
 *  \param system the EkNNSystem.
 *
 *  This is the main function: once you've properly initialized an EkNNSystem, use this function to group the points in clusters using the EkNNclus algorithm as described in "Ek-NNclus: a clustering procedure based on the evidential K-nearest neighbor rule" by Thierry Denoeux, Orakanya Kanjanatarakul and Songsak Sriboonchitta. In this function, we don't compute the evidential part of the algorithm.
 */
void EkNNClusterize(EkNNSystem *system);

//csv.c

/*! \brief Exports the points to CSV.
 *  \param system the EkNNSystem.
 *  \param path the path of export.
 *
 *  Exports the coordinates of the points and the clusters in a csv file. The first line is dedicated to the eastings, whereas each next line corresponds to the northings of a cluster (the first cell of each line stores the label of the cluster).
 */
void EkNNExportToCSV(EkNNSystem *system, char *path);

//util.c

/*! \brief Tosses an array a iter times.
 *  \param a The array to toss.
 *  \param aSize Size of a.
 *  \param iter number of random swaps to do.
 */
void toss(unsigned long *a, unsigned long aSize, unsigned long iter);
/*! \brief Computes the euclidian distance between two EkNNPoints.
 *  \param p1 First point.
 *  \param p2 Second point.
 *  \return Euclidian distance between p1 and p2
 */
double distance(EkNNPoint p1, EkNNPoint p2);
/*! \brief Sorts an array and returns the sorted indexes.
 *  \param s The array to sort.
 *  \param size Size of s.
 *  \return The sorted indexes.
 */
unsigned long *specialSort(double *s, unsigned long size);
/*! \brief Computes the median value of an array.
 *  \param t Array to compute.
 *  \param size Size of t.
 *  \return The median value of t.
 */
double median(double *t, unsigned long size);
/*! \brief Updates the actual number of clusters C in an EkNNSystem and refreshes the labels of the clusters in points.
 *  \param s The EkNNSystem.
 */
void EkNNUpdateC(EkNNSystem *s);

//quicksort.c

/*! \brief Swaps in memory two unsigned long.
 *  \param x Pointer to the first unsigned long.
 *  \param y Pointer to the second unsigned long.
 */
void swapLU(unsigned long *x, unsigned long *y);
/*! \brief Swaps in memory two double.
 *  \param x Pointer to the first double.
 *  \param y Pointer to the second double.
 */
void swapD(double *x, double*y);
/*! \brief Determines a pivot for the quicksort algorithm.
 *  \param i Min value.
 *  \param j Max value.
 *  \return A pivot.
 *
 *  The implementation in quicksort.c uses the mean of i and j as a pivot.
 */
long choose_pivot(long i, long j);
/*! \brief Sorts a list using quicksort algorithm.
 *  \param list The array to sort.
 *  \param indexes Another array that will go through the same swap operations as the list parameter. Just use the NULL pointer if you don't care.
 *  \param m Min value.
 *  \param n Max value.
 *  
 *  This variant of an implementation of the quicksort of algorithm (as found on: http://www.zentut.com/c-tutorial/c-quicksort-algorithm/ ) performs the same swaps on both list and indexes, but sorting list: it can be useful in specific cases, for example when you need to keep the initial positions of the elements in the list.
 */
void quicksort(double *list, unsigned long *indexes, long m, long n);

#endif // _EKNNWINDEV_EKNNWINDEV_H_
