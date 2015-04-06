#pragma once

#include "ProbabilityDistribution.h"

#include <vector>

class PirsonTest
{
private:
	int m_n;
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
	PirsonTest(int n, IProbabilityDistribution * gen) :
		m_n(n), m_gen(gen) {
	};


	double check();
	~PirsonTest();
};

