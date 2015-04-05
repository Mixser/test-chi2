#include <math.h>

#include "ProbabilityDistribution.h"
#include "ICongruentialGenerator.h"

#include <iostream>

IProbabilityDistribution::~IProbabilityDistribution()
{
	delete m_generator;
}

__int64 BernoulliDistribution::nextInt() {
	__int64 result = m_generator->nextDouble() > m_p ? 0 : 1;
	return result;
}


__int64 UniformDistribution::nextInt() {
	double value = m_generator->nextDouble();
	int result = 0;
	for (int i = 0; i < m_n; i++) {
		if (value < m_n)
			return result;
		result += 1;
	}
	return result;
}

__int64 BinomialDistribution::nextInt() {
	__int64 result = 0;
	for (__int64 i = 0; i < m_generators.size(); i++) {
		result += (m_p - m_generators[i]->nextDouble() > 0 ? 1 : 0);
	}

	return result;
}


__int64 NegativeBinomialDistribution::nextInt() {

	__int64 result = 0;
	__int64 k = 0;
	while (k < m_r) {
		int value = m_bernuli->nextInt();
		if (value == 1)  {
			k += 1;
		}
		else {
			result += 1;
		}
	}

	return result;
}

__int64 GeometricDistribution::nextInt() {
	return ceil(log(m_generator->nextDouble()) / log(m_q));
}


void HypergeometricDistribution::generate() {
	m_k = 0;
	m_white = m_d;
	m_black = m_n - m_d;

	for (__int64 j = 0; j < m_m; j++) {
		double p = ((double)m_white) / (m_white + m_black);
		IProbabilityDistribution * bernuli = new BernoulliDistribution(p, m_generator);
		__int64 r = bernuli->nextInt();
		if (r == 1) {
			m_k += 1;
			m_white -= 1;
		}
		else {
			m_sequence.push_back(m_k);
			m_black -= 1;
		}
	}
}


__int64 HypergeometricDistribution::nextInt() {
	while (m_sequence.size() == 0)
		generate();
	__int64 result = m_sequence.front();
	m_sequence.pop_front();
	return result;
}

__int64 PoissonDistribution::nextInt() {
	double B = exp(-m_p);
	double TS = 1;
	int result = 0;
	TS = TS * m_generator->nextDouble();

	while (TS - B > 0) {
		result += 1;
		TS = TS * m_generator->nextDouble();
	}

	return result;
}