#ifndef __GMM__
#define __GMM__

/*
PSEUDOCODE:

Given a dataset and a number of expected distributions K

generate a list of K random Normal distributions with the mean being a random point in the dataset
and all covariances being the dataset covariance
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

#include <LU>
#include <Dense>
#include "common.h"

typedef Eigen::MatrixXd eMatrix;
typedef Eigen::VectorXd epoint_t;
typedef std::pair<epoint_t, eMatrix> Gausian;
typedef epoint_t ProbList;

class GMM
{
	eMatrix dataset;
	eMatrix Y;
	size_t K;
	std::vector<Gausian> gausians;
	ProbList priors;

	epoint_t YikXi(size_t);
	eMatrix YikXi_Uk2(size_t);

public:
	double normal(epoint_t, epoint_t, eMatrix);
	double p(epoint_t);
	void E();
	void M();
	eMatrix covariance();
	eMatrix getMeans();

	GMM(eMatrix, size_t);
	void executeSecuencial();
};

#endif