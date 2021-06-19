#ifndef __COMMON__
#define __COMMON__

#include "lib/allDependencies.h"

typedef double Radius;
typedef std::vector<pointVec> Clusters;
typedef std::pair<point_t, point_t> pointAndCluster;
typedef std::vector<pointAndCluster> ds_t;

const double PI = 2 * acos(0.0);

inline double distance(point_t p1, point_t p2)
{
	double sqrDistance = 0;
	for (int i = 0; i < p1.size(); i++)
	{
		sqrDistance += pow(p1[i] - p2[i], 2);
	}
	return sqrt(sqrDistance);
}

inline size_t minimun(const std::vector<double> &distances)
{
	size_t result = 0;
	for (int i = 1; i < distances.size(); i++)
	{
		if (distances[i] < distances[result])
			result = i;
	}
	return result;
}

inline point_t mean(const pointVec &points, const point_t &p)
{
	if (!points.size()) //points must must have at least 1 point
		return p;
	size_t total = points.size();
	point_t mean(points[0].size());

	for (size_t i = 0; i < mean.size(); i++) //through axis
	{
		mean[i] = 0;
		for (size_t j = 0; j < total; j++)
		{
			mean[i] += points[j][i];
		}
		mean[i] /= total;
	}

	return mean;
}

inline bool operator==(point_t p1, point_t p2)
{
	for (int i = 0; i < p1.size(); i++)
	{
		if (p1[i] != p2[i])
			return false;
	}
	return true;
}
inline bool operator==(pointVec p1, pointVec p2)
{
	for (int i = 0; i < p1.size(); i++)
	{
		if (!(p1[i] == p2[i]))
			return false;
	}
	return true;
}

#endif