#include <iostream>
#include <fstream>
#include <vector>
#include "lib/allDependencies.h"
#include "DBScan.hpp"
#include "Kmeans.hpp"
#include "GMM.hpp"

#define dataset_t std::vector<point_t>

dataset_t getData(std::string path)
{
	rapidcsv::Document doc(path);
	size_t len = doc.GetRowCount();
	dataset_t ds(len);
	for (int i = 0; i < len; i++)
	{
		ds[i] = doc.GetRow<double>(i);
	}
	return ds;
}
eMatrix geteMatrix(std::string path)
{
	rapidcsv::Document doc(path);
	eMatrix ds(doc.GetRowCount(), doc.GetColumnCount());
	for (int i = 0; i < doc.GetRowCount(); i++)
		for (int j = 0; j < doc.GetColumnCount(); j++)
		{
			ds(i, j) = doc.GetRow<double>(i)[j];
		}
	return ds;
}

int main()
{
	std::ofstream output;

	auto ds = getData("data/dataset.csv");
	for (auto &it : ds[0])
	{
		std::cout << it << " ";
	}
	std::cout << "\nafter train\n";

	auto dbscan = DBScan(ds, 20, 5);
	dbscan.executeSecuencial();
	output.open("results/dbscan.csv");
	output << "index,"
				 << "dim1,"
				 << "dim2,"
				 << "cluster"
				 << "\n";
	for (size_t i = 0; i < dbscan.auxiliarDataSet.size(); i++)
	{
		output << i << ","
					 << dbscan.auxiliarDataSet[i].first[0] << ","
					 << dbscan.auxiliarDataSet[i].first[1] << ","
					 << dbscan.getClusterIndex(dbscan.auxiliarDataSet[i].second)
					 << "\n";
	}

	output.close();

	Kmeans kmeans(ds, 7);
	kmeans.executeSecuencial();
	output.open("results/kmeans.csv");
	output << "index,"
				 << "dim1,"
				 << "dim2,"
				 << "cluster"
				 << "\n";
	for (size_t i = 0; i < kmeans.dataSet.size(); i++)
	{
		output << i << ","
					 << kmeans.dataSet[i][0] << ","
					 << kmeans.dataSet[i][1] << ","
					 << kmeans.closestCentroid(kmeans.dataSet[i])
					 << "\n";
	}
	output.close();

	/*
	eMatrix dataset = geteMatrix("data/dataset.csv");
	GMM gmm(dataset, 7);
	gmm.executeSecuencial();
	std::cout << gmm.getMeans();
*/

	return 0;
}