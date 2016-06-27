/*! \file eknnwindev.h
 *  \brief Functions and structures definitions for the EkNNWindev module.
 */

#ifndef _EKNNWINDEV_EKNNWINDEV_H_
#define _EKNNWINDEV_EKNNWINDEV_H_

/*! \brief Container of a two dimensional point
 *
 * Stores the coordinates of a point as well as the label of its cluster.
 */
struct EkNN2DPoint
{
	double x;
	double y;
	cluster integer;
};

typedef struct EkNN2DPoint EkNN2DPoint;

/*! \brief Container of an EkNN two dimensional system.
 *
 * Stores the datas of an EkNN two dimensional system. Must be initialized with EkNNInit(double **points, long K).
 *
 * \var points The points of the system.
 * \var distances N*N array storing the euclidian distances for each point (useful to compute kNN).
 * \var alpha N*K alpha_ik matrix (useful to compute v).
 * \var v N*K v_ik matrix.
 * \var kNN N*K array storing the K nearest neighbours for each point.
 * \var gamma The gamma parameter (useful to compute alpha).
 * \var N Number of points.
 * \var K K parameter for the kNN.
 * \var C Actual number of clusters.
 */
struct EkNN2DSystem
{
	EkNN2DPoint *points;
	double **distances;
	double **alpha;
	double **v;
	double **kNN;
	double gamma;
	int N;
	int K;
	int C;
};

typedef struct EkNN2DSystem EkNN2DSystem;

#endif // _EKNNWINDEV_EKNNWINDEV_H_
