#ifndef __SteeringBehaviors__
#define __SteeringBehaviors__

#include "SVector2D.h"
#include "Character.h"

class SteeringBehaviors{
private:
	class Character *mCharacter;
	class Character *mTarget;
	SVector2D mTargetPosition;
	SVector2D mWanderTarget;

	bool isSeeking = false;
	bool isFleeing = false;
	bool isPersuiting = false;
	bool isWandering = false;
	bool isEvading = false;

public:
	SteeringBehaviors(class Character *character);
	~SteeringBehaviors();

	class Character* target(){
		return mTarget;
	}

	SVector2D seek(SVector2D targetPosition);
	SVector2D flee(SVector2D targetPosition);
	SVector2D persuit(class Character *target);
	SVector2D evade(class Character *target);
	SVector2D wander();

	SVector2D calculate();
	SVector2D forwardComponent();
	SVector2D sideComponent();

	void setPath();
	void setTarget(SVector2D targetPosition);
	void setTarget(Character *target);
	
	void seekOn();
	void fleeOn();
	void evadeOn();
	void persuitOn();
	void wanderOn();

	// Wandering
	double mWanderRadius = 1.2;
	double mWanderDistance = 2.0;
	double mWanderJitter = 80.0;
};

#endif