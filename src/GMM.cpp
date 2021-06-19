#include "GMM.hpp"

GMM::GMM(eMatrix ds, size_t k)
{
	this->K = k;
	this->dataset = ds;

	this->priors = ProbList(k);
	for (size_t i = 0; i < this->K; i++)
		this->priors[i] = 1 / K;

	this->gausians = std::vector<Gausian>(k);

	std::default_random_engine generator;
	std::uniform_int_distribution<int> distribution(0, ds.rows() - 1);

	eMatrix cov = covariance();
	for (auto &pair : this->gausians)
	{
		pair.first = this->dataset.row(distribution(generator));
		pair.second = cov;
	}
	this->Y = eMatrix(this->dataset.rows(), this->K);
}
eMatrix GMM::covariance()
{
	eMatrix &mat = this->dataset;
	eMatrix centered = mat.rowwise() - mat.colwise().mean();
	eMatrix cov = (centered.adjoint() * centered) / double(mat.rows() - 1);
	return cov;
}

double GMM::normal(epoint_t x, epoint_t mean, eMatrix covariance)
{
	double div = sqrt(pow(2 * PI, this->K) * covariance.determinant());
	epoint_t v = x - mean;
	double coe = exp(-0.5 * v.transpose() * covariance.inverse() * v);

	return coe / div;
}

double GMM::p(epoint_t x)
{
	double prob = 0;
	for (size_t i = 0; i < this->K; i++)
	{
		prob += this->priors[i] * normal(x, gausians[i].first, gausians[i].second);
	}
	return prob;
}
void GMM::E()
{
	double div;
	double num;
	epoint_t x;
	for (size_t i = 0; i < this->dataset.rows(); i++)
	{
		x = this->dataset.row(i);
		div = p(x);
		for (size_t j = 0; j < this->K; j++)
		{
			num = this->priors[j] * normal(x, gausians[j].first, gausians[j].second);
			this->Y(i, j) = num / div;
		}
	}
}
void GMM::M()
{
	size_t N = this->dataset.rows();
	double sum;
	for (size_t j = 0; j < this->K; j++)
	{
		sum = this->Y.col(j).sum();
		this->priors[j] = sum / N;
		this->gausians[j].first = YikXi(j) / sum;
		this->gausians[j].second = YikXi_Uk2(j) / sum;
	}
}
epoint_t GMM::YikXi(size_t k)
{
	size_t N = this->dataset.rows();
	auto &mat = this->dataset;
	epoint_t result(mat.cols());
	result.setZero();
	auto temp = result;
	for (size_t i = 0; i < N; i++)
	{
		temp = result + (mat.row(i).transpose() * this->Y(i, k));
		result = temp;
	}
	return result;
}
eMatrix GMM::YikXi_Uk2(size_t k)
{
	size_t N = this->dataset.rows();
	auto &mat = this->dataset;
	epoint_t diff;
	eMatrix result = this->gausians[0].second;
	auto temp = result;
	result.setZero();

	for (size_t i = 0; i < N; i++)
	{
		diff = mat.row(i).transpose() - this->gausians[k].first;
		temp = result + (this->Y(i, k) * (diff * diff.transpose()));
		result = temp;
	}
	return result;
}

eMatrix GMM::getMeans()
{
	size_t N = this->dataset.cols();
	eMatrix means(this->K, N);
	for (size_t i = 0; i < this->K; i++)
		for (size_t j = 0; j < N; j++)
			means(i, j) = this->gausians[i].first[j];

	return means;
}
void GMM::executeSecuencial()
{
	size_t N = this->dataset.cols();
	eMatrix before(this->K, N), after(this->K, N);

	do
	{
		//build before
		before = getMeans();
		E();
		M();
		//build after
		after = getMeans();
	} while (before.isApprox(after, 1));
}