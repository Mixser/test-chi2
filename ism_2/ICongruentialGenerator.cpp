#include "ICongruentialGenerator.h"




__int64 LinearGenerator::nextInt() {
	m_x = (m_a * m_x + m_c) % m_m;
	return m_x;
}



QuadraticGenerator::QuadraticGenerator(__int64 a, __int64 b, __int64 c, __int64 x0, __int64 m)
	:ICongruentialGenerator(x0, m){
	m_a = a;
	m_b = b;
	m_c = c;
}

__int64 QuadraticGenerator::nextInt() {
	m_x = (m_a * (m_x * m_x) + m_b * m_x + m_c) % m_m;
	return m_x;
}