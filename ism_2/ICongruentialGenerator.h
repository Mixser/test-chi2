#include <cstdlib>

#pragma once
class ICongruentialGenerator
{
protected:
	__int64 m_m;
	__int64 m_x;
public:

	ICongruentialGenerator() :
		m_m(0), m_x(0) {};

	ICongruentialGenerator(__int64 x0, __int64 m) : m_m(m), m_x(x0) {}
	virtual __int64 nextInt() = 0;
	
	double nextDouble() {
		return ((double)nextInt()) / m_m;
	}
};


class SystemGenerator : public ICongruentialGenerator {
public:
	SystemGenerator() : ICongruentialGenerator(0, RAND_MAX) {};

	__int64 nextInt() {
		return rand();
	}
};


class LinearGenerator: public ICongruentialGenerator{
private:
	__int64 m_a;
	__int64 m_c;
public:
	LinearGenerator(__int64 a, __int64 c, __int64 x0, __int64 m);

	__int64 nextInt();
};


class QuadraticGenerator : public ICongruentialGenerator {
private:
	__int64 m_a;
	__int64 m_b;
	__int64 m_c;
public:
	QuadraticGenerator(__int64 a, __int64 b, __int64 c, __int64 x0, __int64 m);

	__int64 nextInt();
};