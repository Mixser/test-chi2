#include <iostream>


#include "ICongruentialGenerator.h"

#include "ProbabilityDistribution.h"

#include "Tests.h"

#include <vector>
#include <map>

#include <fstream>



void output_to_csv(const char * fileName, IProbabilityDistribution * gen, int count){
	std::ofstream file(fileName);

	std::map<__int64, __int64> out;

	for (int i = 0; i < count; i++) {
		__int64 value = gen->nextInt();
		if (out.find(value) == out.end()) {
			out[value] = 1;
		}
		else {
			out[value] += 1;
		}
	}

	for (std::map<__int64, __int64>::iterator it = out.begin(); it != out.end(); it++) {
		file << it->first << "; " << it->second << std::endl;
	}

	file.close();
}

std::vector<ICongruentialGenerator *> create_generators(int m) {
	std::vector<ICongruentialGenerator * > result;
	for (int i = 0; i < m; i++)
	{
		__int64 s = 4294967295;
		__int64 seed = rand() % 100000;
		ICongruentialGenerator * gen = new LinearGenerator(48271, 0, seed, s);
		result.push_back(gen);
	}
	return result;
}

int main(int argc, char ** argv) {
	ICongruentialGenerator * sys = new SystemGenerator();
	__int64 s = 4294967295;
	ICongruentialGenerator * lin = new LinearGenerator(48271, 0, 105, s);

	IProbabilityDistribution *p1 = new BernoulliDistribution(0.3, lin);
	IProbabilityDistribution *p2 = new UniformDistribution(lin,10);
	IProbabilityDistribution *p3 = new BinomialDistribution(0.4, create_generators(12));
	IProbabilityDistribution *p4 = new NegativeBinomialDistribution(0.2, 100, lin);
	IProbabilityDistribution *p5 = new GeometricDistribution(0.2, lin);
	IProbabilityDistribution *p6 = new HypergeometricDistribution(100, 100, 32, lin);
	IProbabilityDistribution *p7 = new PoissonDistribution(10, lin);


	std::cout << PirsonTest(10000, p7).check() <<std::endl;


	//output_to_csv("out.csv", p3, 10000);
	return 0;
}