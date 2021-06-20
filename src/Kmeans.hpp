#ifndef __KMEANS__
#define __KMEANS__

/*
PSEUDOCODE:

Given a dataset, and K

choose K random points (centroids) from the dataset |> this to be always in the limits of the dataset

Repeat until the centroids converge:

	compute the distance between every point and the K centroids

	assing the cluster of a point to be the closest centroid

	update the centroids to be the mean of the points belonging to it
*/

#include "common.h"

class Kmeans
{
	size_t K;
	pointVec centroids;
	Clusters clusters;

	void resetClusters();
	void assignCluster(point_t);
	void computeCentroids();

public:
	pointVec dataSet;
	Kmeans(const pointVec &, size_t);
	size_t closestCentroid(point_t);
	void executeSecuencial();
	pointVec getCentroids();
};

#endif