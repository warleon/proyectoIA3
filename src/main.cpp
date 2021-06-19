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
	/*
	auto ds = getData("data/dataset.csv");
	for (auto &it : ds[0])
	{
		std::cout << it << " ";
	}
	std::cout << "\nafter train\n";
	*/

	/*
	auto dbscan = DBScan(ds, 20, 8);

	dbscan.executeSecuencial();
	for (int i = 0; i < 10; i++)
	{
		std::cout << "\n-----point-----\n";
		for (auto &it : dbscan.auxiliarDataSet[i].first)
		{
			std::cout << it << " ";
		}
		std::cout << "\n-----cluster-----\n";
		for (auto &it : dbscan.auxiliarDataSet[i].second)
		{
			std::cout << it << " ";
		}
	}
	*/

	/*
	Kmeans kmeans(ds, 7);
	kmeans.executeSecuencial();
	for (auto &it : kmeans.getCentroids())
	{
		for (auto &it2 : it)
		{
			std::cout << it2 << " ";
		}
		std::cout << "\n";
	}

	std::cout << "\n";
	Matrix a =
			{{1, 2, 4},
			 {2, -1, 3},
			 {4, 0, 1}};

	Matrix m = GMM::subMatrix(a, 1, 1);
	for (auto &it : m)
	{
		for (auto &it2 : it)
		{
			std::cout << it2 << " ";
		}
		std::cout << "\n";
	}
	std::cout << GMM::det(a) << "\n";
*/
	eMatrix dataset = geteMatrix("data/dataset.csv");
	GMM gmm(dataset, 7);
	gmm.executeSecuencial();
	std::cout << gmm.getMeans();

	return 0;
}