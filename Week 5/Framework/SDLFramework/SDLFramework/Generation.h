#ifndef __GENERATION__
#define __GENERATION__

#include "Instance.h"
#include <vector>

using namespace std;


class Generation {
private:
	vector<Instance *> mGeneration;

	int totalPoints();
	void noDominance(int totalValue);

	vector<Instance *> bestChances(int totalValue);
	vector<Instance *> secondChances(int totalValue);

	Instance* newInstance(int ID, Instance *parent1, Instance *parent2);

public:
	Generation(vector<Instance *> generation);
	~Generation();

	vector<Instance *> newGeneration();
};

#endif