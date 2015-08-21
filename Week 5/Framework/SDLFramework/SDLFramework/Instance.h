#ifndef __INSTANCE__
#define __INSTANCE__

#include <vector>
#include "Cow.h"
#include "Bunny.h"
#include "Item.h"

using namespace std;

class Instance{
private:
	void defineColor();
public:
	Instance(int ID);
	~Instance();

	int mID = 0;

	Cow *mCow = nullptr;
	Bunny *mBunny = nullptr;
	Item *mWeapon = nullptr;
	Item *mPill = nullptr;


	void addToWorld();
	void removeFromWorld();

	void setDefaultStates();
	void setCowStateChance();
	void setCowStateChance(int flee, int fleeAndSearchPill, int hide, int fleeAndSearchWeapon);
	
};

#endif


