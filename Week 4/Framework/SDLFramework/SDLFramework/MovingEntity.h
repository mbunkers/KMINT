#ifndef __MovingEntity__
#define __MovingEntity__

#include "IGameObject.h"
#include "SVector2D.h"

class MovingEntity : public IGameObject{
protected:
	SVector2D mVelocity;
	SVector2D mHeading;
	SVector2D mSide;

	

	double mSpeed;
	double mMass;
	double mMaxSpeed;
	double mMaxForce;
	double mMaxTurnRate;

private:
public:
	MovingEntity();
	~MovingEntity();

	double speed()			{ return mSpeed; }
	double mass()			{ return mMass; }
	double maxSpeed()		{ return mMaxSpeed; }
	double maxForce()		{ return mMaxForce; }
	double maxTurnRate()	{ return mMaxTurnRate; }
	SVector2D heading()		{ return mHeading; }
	SVector2D velocity()		{ return mVelocity; }
	SVector2D side()			{ return mSide; }
};

#endif