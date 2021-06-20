#ifndef _dbscan_
#define _dbscan_
/*
PSEUDOCODE:
  Given a dataset, a radius and a minimum cluster size

  For every point in the dataset:

    If the point has been already visited skip it

    Else

      Get all the points in a CIRCLE of radius RADIUS and centered to the CURRENT POINT

      If the amount of points if less than the MINIMUM CLUSTER SIZE set its centers to the default cluster

    Else

      Set the center of THIS CLUSTER to be the CURRENT POINT

      For every point within the previus defined CIRCLE:

        If it belong to any non default cluster skip it

        Else:

          set the center of ITS CLUSTER to be the center of THIS CLUSTER

          Get all the points in a CIRCLE of radius RADIUS and centered to the CURRENT POINT

          If the amount of points if greater or equal than the MINIMUM CLUSTER SIZE expand the set of point of this loop

*/
#include "common.h"

class DBScan
{
  size_t min;
  Radius r;
  KDTree dataset;
  std::vector<point_t> clusters;

  static void singlePointDBScan(DBScan *, pointAndCluster *);

public:
  ds_t auxiliarDataSet; //since the KDTree doesn't provide a way to traverse through this is needed;

  DBScan(const pointVec &, const Radius &, size_t);
  void executeSecuencial();
  int getCluster(point_t);
};
#endif