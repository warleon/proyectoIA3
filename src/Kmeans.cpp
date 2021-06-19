#include "Kmeans.hpp"

Kmeans::Kmeans(const pointVec &ds, size_t K)
{
	this->K = K;
	this->centroids = pointVec(this->K);
	this->dataSet = pointVec(ds);

	std::default_random_engine generator;
	std::uniform_int_distribution<int> distribution(0, ds.size() - 1);
	for (auto &it : this->centroids)
	{
		it = this->dataSet[distribution(generator)];
	}

	resetClusters();
}
void Kmeans::resetClusters()
{
	this->clusters = Clusters(this->K);
}
size_t Kmeans::closestCentroid(point_t p)
{
	std::vector<double> distances(this->K);

	for (size_t i = 0; i < distances.size(); i++)
	{
		distances[i] = distance(p, this->centroids[i]);
	}
	return minimun(distances);
}
void Kmeans::assignCluster(point_t p)
{
	clusters[closestCentroid(p)].push_back(p);
}
void Kmeans::computeCentroids()
{
	for (size_t i = 0; i < this->K; i++)
	{
		this->centroids[i] = mean(this->clusters[i], this->centroids[i]);
	}
}
void Kmeans::executeSecuencial()
{
	pointVec before;
	do
	{
		before = this->centroids;

		resetClusters();

		for (size_t i = 0; i < this->dataSet.size(); i++)
		{
			assignCluster(dataSet[i]);
		}

		computeCentroids();

	} while (!(before == this->centroids));
}
pointVec Kmeans::getCentroids()
{
	return this->centroids;
}