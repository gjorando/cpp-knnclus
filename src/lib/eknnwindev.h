/*! \file eknnwindev.h
 *  \brief Functions and structures definitions for the EkNNWindev module.
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

typedef struct EkNNPoint EkNNPoint; //!< Alias for the struct EkNNPoint

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

typedef struct EkNNSystem EkNNSystem; //!< Alias for the struct EkNNSystem

// FUNCTION DEFINITIONS

// init.c
EkNNSystem *EkNNInit(double **points, unsigned long N, unsigned long K);
void EkNNDestroy(EkNNSystem *s);

void EkNNInitClusters(EkNNSystem *result);
void EkNNInitDistances(EkNNSystem *result);
void EkNNInitKNN(EkNNSystem *result);
void EkNNInitGamma(EkNNSystem *result);
void EkNNInitAlpha(EkNNSystem *result);
void EkNNInitV(EkNNSystem *result);

//general.c
void EkNNDisplay(EkNNSystem *foo);
void EkNNClusterize(EkNNSystem *system);

//util.c

void toss(unsigned long *a, unsigned long aSize, unsigned long iter);
double distance(EkNNPoint p1, EkNNPoint p2);
unsigned long *specialSort(double *s, unsigned long size);
double median(double *t, unsigned long size);
void EkNNUpdateC(EkNNSystem *s);

#endif // _EKNNWINDEV_EKNNWINDEV_H_
