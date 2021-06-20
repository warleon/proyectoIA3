#include <iostream>
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
	auto ds = getData("data/dataset.csv");
	for (auto &it : ds[0])
	{
		std::cout << it << " ";
	}
	std::cout << "\nafter train\n";

	auto dbscan = DBScan(ds, 20, 8);
	dbscan.executeSecuencial();

	Kmeans kmeans(ds, 7);
	kmeans.executeSecuencial();

	/*
	eMatrix dataset = geteMatrix("data/dataset.csv");
	GMM gmm(dataset, 7);
	gmm.executeSecuencial();
	std::cout << gmm.getMeans();
*/

	return 0;
}