/*! \file eknnwindev.h
 *  \brief Functions and structures definitions for the EkNNWindev module.
 */

#ifndef _EKNNWINDEV_EKNNWINDEV_H_
#define _EKNNWINDEV_EKNNWINDEV_H_

// STRUCTURE DEFINITIONS

/*! \brief Container of a two dimensional point.
 *
 *  Stores the coordinates of a point as well as the label of its cluster.
 */
struct EkNN2DPoint
{
	double x; //!< Easting of the point.
	double y; //!< Northing of the point.
	cluster integer; //!< Label for the cluster of the point.
};

typedef struct EkNN2DPoint EkNN2DPoint; //!< Alias for the struct EkNN2DPoint

/*! \brief Container of an EkNN two dimensional system.
 *
 *  Stores the datas of an EkNN two dimensional system. Must be initialized with EkNNInit(double **points, long K).
 */
struct EkNN2DSystem
{
	EkNN2DPoint *points; //!< The points of the system.
	double **distances; //!< N*N array storing the euclidian distances for each point (useful to compute kNN).
	double **alpha; //!< N*K alpha_ik matrix (useful to compute v).
	double **v; //!< N*K v_ik matrix.
	double **kNN; //!< N*K array storing the K nearest neighbours for each point.
	double gamma; //!< The gamma parameter (useful to compute alpha).
	int N; //!< Number of points.
	int K; //!< K parameter for the kNN.
	int C; //!< Actual number of clusters.
};

typedef struct EkNN2DSystem EkNN2DSystem; //!< Alias for the struct EkNN2DSystem

// FUNCTION DEFINITIONS



#endif // _EKNNWINDEV_EKNNWINDEV_H_
