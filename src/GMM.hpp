#ifndef __GMM__
#define __GMM__

/*
PSEUDOCODE:

Given a dataset and a number of expected distributions K

generate a list of K random Normal distributions with the mean being a random point in the dataset
and all covariances being the sample covariances
and a list of K prior probabilities being 1/K

Repeat until convergence of (prior,mean and covariance):

	compute for every i and k:

		Yik =
		 						PRIOR_k * Normal(X_i,mean_k,covariance_k) 
		 ----------------------------------------------------------------
		 SUM from j=1 to K of (PRIOR_j * Normal(X_i,mean_j,covariance_j))

	compute for every k:

		prior_k = (SUM from i=1 to N of (Yik))/N

		mean_k =
							(SUM from i=1 to N of (Yik*X_i))
					----------------------------------------
								(SUM from i=1 to N of (Yik))

		covariance_k = 
							(SUM from i=1 to N of (Yik*(X_i-mean_k)**2))
					----------------------------------------------------
											(SUM from i=1 to N of (Yik))
*/

#include "common.h"

typedef std::vector<std::vector<double>> Matrix;

class GMM
{
	pointVec dataset;
	size_t K;

public:
	static Matrix subMatrix(Matrix, size_t, size_t);
	static double normal(point_t, point_t, Matrix);
	static double det(Matrix);

	GMM(pointVec, size_t);
	void executeSecuencial();
};

#endif