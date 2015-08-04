#include "SteeringBehaviors.h"
#include "FWApplication.h"
#include "Transformations.h"
#include "Util.h"

SteeringBehaviors::SteeringBehaviors(Character *character){
	mCharacter = character;
	double theta = RandFloat() * TwoPi;

	//create a vector to a target position on the wander circle
	mWanderTarget = SVector2D(mWanderRadius * cos(theta),
		mWanderRadius * sin(theta));
}


SteeringBehaviors::~SteeringBehaviors(){
}

void SteeringBehaviors::setTarget(SVector2D position){
	mTargetPosition = position;
}

void SteeringBehaviors::setTarget(Character *target){
	mTarget = target;
}

SVector2D SteeringBehaviors::calculate(){
	SVector2D steering = SVector2D();

	if (isFleeing){
		steering += persuit(mTarget);
	}
	if (isWandering){
		SVector2D wanderForce = wander();
		steering = steering + wanderForce;
	}
	if (isPersuiting){
		SVector2D persuitForce = persuit(mTarget);
		steering = (steering + persuit(mTarget));
	}
	if (isSeeking){
		steering += seek(mTarget->position());
	}
	if (isEvading){
		SVector2D evadeForce = evade(mTarget);
		steering = steering + evadeForce;
	}

	return steering;
}

void SteeringBehaviors::seekOn(){
	isSeeking = true;
	isFleeing = false;
	isEvading = false;
	isPersuiting = false;
	isWandering = false;
}
void SteeringBehaviors::fleeOn(){
	isSeeking = false;
	isFleeing = true;
	isEvading = false;
	isPersuiting = false;
	isWandering = false;
}
void SteeringBehaviors::evadeOn(){
	isSeeking = false;
	isFleeing = false;
	isEvading = true;
	isPersuiting = false;
	isWandering = false;
}
void SteeringBehaviors::persuitOn(){
	isSeeking = false;
	isFleeing = false;
	isEvading = false;
	isPersuiting = true;
	isWandering = false;
}
void SteeringBehaviors::wanderOn(){
	isSeeking = false;
	isFleeing = false;
	isEvading = false;
	isPersuiting = false;
	isWandering = true;
}

SVector2D SteeringBehaviors::seek(SVector2D targetPosition){
	SVector2D desiredVelocity = Vec2DNormalize(targetPosition - mCharacter->position()) * mCharacter->maxSpeed();
	return desiredVelocity - mCharacter->velocity();
}

SVector2D SteeringBehaviors::flee(SVector2D targetPosition){
	const double panicDistanceSq = 100.0 * 100.0;
	if (Vec2DDistance(mCharacter->position(), targetPosition) > panicDistanceSq){
		return SVector2D(0,0);
	}

	SVector2D desiredVelocity = Vec2DNormalize(mCharacter->position() - targetPosition) * mCharacter->maxSpeed();
	return desiredVelocity - mCharacter->velocity();
}

SVector2D SteeringBehaviors::persuit(Character *target){
	SVector2D toEvader = target->position() - mCharacter->position();

	double relativeHeading = mCharacter->heading().Dot(target->heading());

	if ((toEvader.Dot(mCharacter->heading()) > 0) && (relativeHeading < -0.95)){
		return seek(target->position());
	}

	double lookAheadTime = toEvader.Length() / (mCharacter->maxSpeed() + target->speed());
	return seek(target->position() + target->velocity() * lookAheadTime);
}

SVector2D SteeringBehaviors::evade(Character *target){
	/* Not necessary to include the check for facing direction this time */

	SVector2D ToPursuer = target->position() - mCharacter->position();

	//uncomment the following two lines to have Evade only consider pursuers 
	//within a 'threat range'
	const double ThreatRange = 100.0;
	if (ToPursuer.LengthSq() > ThreatRange * ThreatRange){
		return SVector2D();
	}

	//the lookahead time is propotional to the distance between the pursuer
	//and the pursuer; and is inversely proportional to the sum of the
	//agents' velocities
	double LookAheadTime = ToPursuer.Length() /
		(mCharacter->maxSpeed() + target->speed());

	//now flee away from predicted future position of the pursuer
	return flee(target->position() + target->velocity() * LookAheadTime);
}

SVector2D SteeringBehaviors::wander(){
	//first, add a small random vector to the target's position
	mWanderTarget += SVector2D(RandomClamped() * mWanderJitter,
		RandomClamped() * mWanderJitter);

	//reproject this new vector back on to a unit circle
	mWanderTarget.Normalize();

	//increase the length of the vector to the same as the radius
	//of the wander circle
	mWanderTarget = mWanderTarget * mWanderRadius;

	//move the target into a position WanderDist in front of the agent
	SVector2D targetLocal = mWanderTarget + SVector2D(mWanderDistance, 0);

	//project the target into world space
	SVector2D targetWorld = PointToWorldSpace(targetLocal, mCharacter->heading(), mCharacter->side(), mCharacter->position());

	//and steer towards it
	return targetWorld - mCharacter->position();
}
