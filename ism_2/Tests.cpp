#include "Tests.h"


double PirsonTest::check() {
	__int64 minimum = min();
	__int64 maximum = max();
	double h = 1.0 * (maximum - minimum) / m_k;

	segments.push_back(minimum + h);

	for (int i = 1; i < m_k; i++) {
		segments.push_back(segments[i - 1] + h);
	}

	for (int i = 0; i < m_n; i++)
	{
		int j = 0;
		while (sequence[i] > segments[j])
		{
			j++;
			if (j == m_k)
			{
				j--;
				break;
			}
		}
		frequency[j]++;
	}

	double hi = 0;
	for (int j = 0; j < m_k; ++j) {
		double h = pow(frequency[j] - m_n * m_gen->probability_func(j), 2);
		double d = m_gen->probability_func(j) * m_n;
		hi += h / d;
	}

	return hi;

}

PirsonTest::~PirsonTest()
{
}
