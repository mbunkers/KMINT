#ifndef __COW__
#define __COW__


#include "Character.h"
#include "Node.h"
#include "AStar.h"
#include "SearchState.h"
#include "ChaseState.h"

class Cow : public Character{
private: 
	int mStateChangeCounter = 3;

	int mFleeChance = 0;
	int mFleePillSearchChance = 0;
	int mHideChance = 0;
	int mFleeAndWeaponSearchChance = 0;

public:
	Cow(SDL_Texture *texture, Node *startNode);
	~Cow();

	int fleeChance(){
		return mFleeChance;
	}
	void setFleeChance(int chance){
		mFleeChance = chance;
	}
	int fleePillSearchChance(){
		return mFleePillSearchChance;
	}
	void setFleePillSearchChance(int chance){
		mFleePillSearchChance = chance;
	}
	int hideChance(){
		return mHideChance;
	}
	void setHideChance(int chance){
		mHideChance = chance;
	}
	int fleeAndWeaponSearchChance(){
		return mFleeAndWeaponSearchChance;
	}
	void setFleeAndWeaponSearchChance(int chance){
		mFleeAndWeaponSearchChance = chance;
	}

	void Update(float deltaTime);
	void respawn();
	void defaultState();
	void move();
	void changeTarget(Character *target);
	void changeTarget(Cow *target);
	void changeState();
};

#endif

