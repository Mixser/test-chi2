#include "Tests.h"

#include <map>

#include <iostream>


double PirsonTest::check() {
	std::map<__int64, __int64> out;

	for (int i = 0; i < m_n; i++) {
		__int64 value = m_gen->nextInt();
		if (out.find(value) == out.end()) {
			out[value] = 1;
		}
		else {
			out[value] += 1;
		}
	}

	double hi = 0;
	for (std::map<__int64, __int64>::iterator it = out.begin(); it != out.end(); it++) {
		std::cout << it->first << " " << it->second << std::endl;
		double h = it->second - m_n * m_gen->probability_func(it->first);
		
		h = h * h;

		double d = m_gen->probability_func(it->first) * m_n;
		hi += h / d;
	}


	return hi;

}

PirsonTest::~PirsonTest()
{
}
