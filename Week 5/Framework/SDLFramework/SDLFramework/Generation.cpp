#include "Generation.h"


Generation::Generation(vector<Instance *> generation){
	for (size_t i = 0; i < generation.size(); i++){
		mGeneration.push_back(generation.at(i));
	}
}


Generation::~Generation(){
}

int Generation::totalPoints(){
	int totalValue = 0;
	for (size_t i = 0; i < mGeneration.size(); i++){
		Instance *instance = mGeneration.at(i);
		totalValue += instance->mCow->mTargetPoints;
		printf("Instance %d: %d punten\n", i, instance->mCow->mTargetPoints);
	}
	printf("Totale waarde: %d\n", totalValue);
	return totalValue;
}

void Generation::noDominance(int totalValue){
	if (totalValue == 0){
		for (size_t i = 0; i < mGeneration.size(); i++){
			Instance *instance = mGeneration.at(i);
			instance->mCow->mTargetPoints = 1;
		}
	}
}

vector<Instance *> Generation::bestChances(int totalValue){
	vector<Instance *> chances = vector<Instance *>();

	for (size_t i = 0; i < mGeneration.size(); i++){
		Instance *instance = mGeneration.at(i);
		double chance = (double)instance->mCow->mTargetPoints / (double)totalValue * mGeneration.size();
		printf("Instance %d expected: %f\n", i, chance);
		if ((int)chance >= 1){
			chances.push_back(instance);
		}
	}

	return chances;
}

vector<Instance *> Generation::secondChances(int totalValue){
	vector<Instance *> chances = vector<Instance *>();

	while (chances.size() != mGeneration.size()){
		Instance *highestInstance = nullptr;
		double highest = -1;

		for (size_t i = 0; i < mGeneration.size(); i++){
			Instance *instance = mGeneration.at(i);
			double chance = (double)instance->mCow->mTargetPoints / (double)totalValue * mGeneration.size();
			chance = chance - (long)chance;

			if (chance > highest){
				bool isAdded = false;
				for (size_t i = 0; i < chances.size(); i++){
					Instance *testInstance = chances.at(i);
					if (instance == testInstance){
						isAdded = true;
					}
				}
				if (!isAdded){
					highest = chance;
					highestInstance = instance;
				}
			}
		}

		chances.push_back(highestInstance);
	}

	return chances;
}

Instance* Generation::newInstance(int ID, Instance *parent1, Instance *parent2){
	int chance1 = parent1->mCow->fleeChance();
	int chance2 = parent1->mCow->fleePillSearchChance();
	int chance3 = parent2->mCow->hideChance();
	int chance4 = parent2->mCow->fleeAndWeaponSearchChance();

	Instance *subject = new Instance(ID);

	subject->setCowStateChance(chance1, chance2, chance3, chance4);
	
	int parent1Points = parent1->mCow->mTargetPoints;
	int parent2Points = parent2->mCow->mTargetPoints;

	int targetPoints = parent1Points / 2 + parent2Points / 2;

	subject->mCow->mTargetPoints = targetPoints;

	return subject;
}

vector<Instance *> Generation::newGeneration(){
	// Calculate totalPoints, if zero then give all 1 point
	int totalValue = totalPoints();
	
	vector<Instance *> participation = vector<Instance *>();
	
	if (totalValue != 0){
		vector<Instance *> bestChance = bestChances(totalValue);
		for (size_t i = 0; i < bestChance.size(); i++){
			Instance *instance = bestChance.at(i);
			participation.push_back(instance);
		}
	}

	vector<Instance *> secondChance = secondChances(totalValue);
	size_t counter = 0;
	while (participation.size() != mGeneration.size()){
		participation.push_back(secondChance.at(counter));
		counter++;
	}

	for (size_t i = 0; i < participation.size(); i++){
		Instance *instance = participation.at(i);
		printf("Participant: Koe%d\n", instance->mID);
	}


	vector<Instance *> newGeneration = vector<Instance *>();
	for (size_t i = 0; i < participation.size(); i += 2){
		newGeneration.push_back(newInstance(i, participation.at(i), participation.at(i + 1)));
		newGeneration.push_back(newInstance(i + 1, participation.at(i), participation.at(i + 1)));
	}

	for (size_t i = 0; i < newGeneration.size(); i++){
		Instance *instance = newGeneration.at(i);
		printf("Subject: Koe%d(%d)\n", instance->mID, instance->mCow->mTargetPoints);
	}

	printf("\n\n");
	return newGeneration;
}
