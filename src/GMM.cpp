#include "GMM.hpp"

GMM::GMM(pointVec ds, size_t k)
{
	this->K = k;
	this->dataset = pointVec(ds);
}

double GMM::normal(point_t x, point_t mean, Matrix covariance)
{
}

Matrix GMM::subMatrix(Matrix A, size_t I, size_t J)
{
	Matrix ret;
	size_t row;

	for (size_t i = 0; i < A.size(); i++)
	{
		if (i == I)
			continue;

		ret.push_back(std::vector<double>());
		row = ret.size() - 1;
		for (size_t j = 0; j < A[i].size(); j++)
		{
			if (j == J)
				continue;
			ret[row].push_back(A[i][j]);
		}
	}
	return ret;
}

double GMM::det(Matrix A)
{
	if (!A.size())
		return 1;

	double result = 0;
	double alt = 1;
	for (size_t j = 0; j < A[0].size(); j++)
	{
		result += alt * A[0][j] * det(subMatrix(A, 0, j));
		alt *= -1;
	}
	return result;
}

void GMM::executeSecuencial()
{
}