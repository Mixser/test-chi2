#pragma once

#include <vector>
#include <deque>

#include "ICongruentialGenerator.h"

class ICongruentialGenerator;



class IProbabilityDistribution
{
protected:
	ICongruentialGenerator * m_generator;
	double factorial(int n)
	{
		if (n < 0)
			return 0;
		return (n = 1 || n == 0) ? 1.0 : factorial(n - 1) * n;
	}

	double binom(int n, int k) {
		if (n - k < 0) {
			return 0;
		}
		double result = 1.0;
		for (int i = 1; i <= k; i++) {
			result = result * (n - k + i) * 1.0 / (i * 1.0);
		}
		return result;
	}
public:
	IProbabilityDistribution() : m_generator(NULL){};
	IProbabilityDistribution(ICongruentialGenerator * gen)
		: m_generator(gen) {};

	virtual double probability_func(__int64 x) = 0;
	virtual ~IProbabilityDistribution();

	virtual __int64 nextInt() = 0;
};


class BernoulliDistribution : public IProbabilityDistribution {
private:
	double m_p;
public:
	BernoulliDistribution(double p, ICongruentialGenerator* gen)
		:IProbabilityDistribution(gen), m_p(p) {};


	double probability_func(__int64 x){
		if (x == 0) {
			return 1.0 - m_p;
		}
		else {
			return m_p;
		}
	}
	__int64 nextInt();
};


class UniformDistribution : public IProbabilityDistribution {
private:
	double m_n;
public:
	UniformDistribution(ICongruentialGenerator * gen, int n) : m_n(n),
		IProbabilityDistribution(gen) {}

	double probability_func(__int64 x){
		return  1.0 / m_n;
	}
	__int64 nextInt();
};


class BinomialDistribution : public IProbabilityDistribution {
private:
	std::vector<ICongruentialGenerator * > m_generators;
	double m_p;
public:
	BinomialDistribution(double p, std::vector<ICongruentialGenerator * > gens) 
		: m_generators(gens), m_p(p)  {};

	double probability_func(__int64 x)
	{
		return binom(m_generators.size(), x) * pow(m_p, x) * pow(1 - m_p, m_generators.size() - x);
	}

	__int64 nextInt();
};


class NegativeBinomialDistribution : public IProbabilityDistribution {
private:
	BernoulliDistribution * m_bernuli;
	double m_p;
	__int64 m_r;
public:
	NegativeBinomialDistribution(double p, int r, ICongruentialGenerator * gen)
		: IProbabilityDistribution(gen), m_p(p), m_r(r)  {

		m_bernuli = new BernoulliDistribution(p, gen);

	};

	~NegativeBinomialDistribution() {
		delete m_generator;
		m_generator = NULL;
	}

	double probability_func(__int64 x) {
		return binom(x + m_r - 1, x) * pow(m_p, m_r) * (1 - m_p, x);
	}

	__int64 nextInt();
};


class GeometricDistribution : public IProbabilityDistribution{
private:
	double m_p;
	double m_q;
public:
	GeometricDistribution(double p, ICongruentialGenerator * gen)
		: m_p(p), m_q(1 - p), IProbabilityDistribution(gen) {};

	double probability_func(__int64 x) {
		return pow(m_q, x) * m_p;
	}

	__int64 nextInt();
};


class HypergeometricDistribution : public IProbabilityDistribution {
private:
	__int64 m_n, m_d;
	__int64 m_m;
	__int64 m_k;

	__int64 m_white, m_black;

	

	std::deque<int> m_sequence;

	void generate();

public:

	HypergeometricDistribution(__int64 m, __int64 n, __int64 d, ICongruentialGenerator * gen)
		: IProbabilityDistribution(gen)	{
		
		m_n = n;
		m_m = m;
		m_d = d;
		m_white = d;
		m_black = n - d;

		generate();
	};

	double probability_func(__int64 x) {
		return binom(m_d, x) * binom(m_n - m_d, m_m - x) / binom(m_n, m_m);
	}

	__int64 nextInt();

	
};


class PoissonDistribution : public IProbabilityDistribution {
private:
	double m_p;

public:
	PoissonDistribution(double p, ICongruentialGenerator * gen) : m_p(p), IProbabilityDistribution(gen) {};

	double probability_func(__int64 x) {
		double result = pow(m_p, x) * exp(-m_p);
		for (int i = 1; i <= x; i++)
			result = result /  (i * 1.0);
		return  result;
	}

	__int64 nextInt();

};
