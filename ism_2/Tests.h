#pragma once

#include "ProbabilityDistribution.h"

#include <vector>

class PirsonTest
{
private:
	int m_n;
	int m_k;
	IProbabilityDistribution * m_gen;

	std::vector<__int64> sequence;

	std::vector<double> segments;
	std::vector<__int64> frequency;

	__int64 min() {
		__int64 result = UINT_MAX;
		for (int i = 0; i < sequence.size(); i++)
			if (result > sequence[i])
				result = sequence[i];
		return result;
	}

	__int64 max() {
		__int64 result = -1;
		for (int i = 0; i < sequence.size(); i++)
			if (result < sequence[i])
				result = sequence[i];
		return result;
	}

	
public:
	PirsonTest(int n, int k, IProbabilityDistribution * gen) :
		m_n(n), m_k(k), m_gen(gen) {

		for (int i = 0; i < m_n; i++){
			sequence.push_back(gen->nextInt());
		}
		for (int i = 0; i < m_k; i++)
			frequency.push_back(0);
	};


	double check();
	~PirsonTest();
};

