#include "DBScan.hpp"

DBScan::DBScan(const pointVec &dataset, const Radius &radius, size_t minimum)
{
  this->r = radius;
  this->dataset = KDTree(dataset);
  this->min = minimum;

  for (int i = 0; i < dataset.size(); i++)
    this->auxiliarDataSet.push_back(std::make_pair(dataset[i], point_t(dataset[i].size(), -1)));
}

void DBScan::singlePointDBScan(DBScan *self, pointAndCluster *p1)
{
  if (distance(p1->second, point_t(p1->first.size(), -1)) > 0) //if already has cluster
    return;

  point_t center = p1->first;
  pointIndexArr nearests = self->dataset.neighborhood(center, self->r);
  std::set<size_t> path;

  if (nearests.size() < self->min)
    return;

  p1->second = center;
  for (auto &p : nearests)
    path.insert(p.second);

  size_t i = 0;
  pointIndexArr toExpand;
  for (auto &p : path)
  {
    toExpand = self->dataset.neighborhood(self->auxiliarDataSet[p].first, self->r);
    if (nearests.size() < self->min)
      continue;

    for (auto &it : toExpand)
      path.insert(it.second);
  }

  for (auto &i : path)
    self->auxiliarDataSet[i].second = center;

  if (std::find(self->clusters.begin(), self->clusters.end(), center) == self->clusters.end())
    self->clusters.push_back(center);
}

void DBScan::executeSecuencial()
{
  for (size_t i = 0; i < auxiliarDataSet.size(); i++)
  {
    DBScan::singlePointDBScan(this, &auxiliarDataSet[i]);
  }
}
int DBScan::getClusterOf(point_t p)
{
  size_t n = this->dataset.nearest_index(p);
  point_t cluster = this->auxiliarDataSet[n].second;
  return getClusterIndex(cluster);
}
int DBScan::getClusterIndex(point_t c)
{
  for (size_t i = 0; i < this->clusters.size(); i++)
  {
    if (c == this->clusters[i])
      return i;
  }
  return -1;
}