#include "SteeringBehaviors.h"
#include "FWApplication.h"
#include "Transformations.h"
#include "Util.h"
#include "Cow.h"

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
		SVector2D fleeForce = flee(mTarget->position());
		steering = steering + fleeForce;
	}
	if (isSeeking){
		if (steering.isZero()){
			SVector2D seekForce = seek(mTargetPosition);
			steering = steering + seekForce;
		}
	}
	if (isWandering){
		SVector2D wanderForce = wander();
		steering = steering + wanderForce;
	}
	if (isPersuiting){
		SVector2D persuitForce = persuit(mTarget);
		steering = (steering + persuit(mTarget));
	}
	if (isEvading){
		SVector2D evadeForce = evade(mTarget);
		steering = steering + (evadeForce * 0.8);
	}

	return steering;
}

void SteeringBehaviors::seekOn(){
	isSeeking = true;
}
void SteeringBehaviors::fleeOn(){
	isFleeing = true;
}
void SteeringBehaviors::evadeOn(){
	isEvading = true;
}
void SteeringBehaviors::persuitOn(){
	isPersuiting = true;
}
void SteeringBehaviors::wanderOn(){
	isWandering = true;
}

void SteeringBehaviors::reset(){
	isSeeking = false;
	isFleeing = false;
	isEvading = false;
	isPersuiting = false;
	isWandering = false;
}

SVector2D SteeringBehaviors::seek(SVector2D targetPosition){
	SVector2D desiredVelocity = Vec2DNormalize(targetPosition - mCharacter->position()) * mCharacter->maxSpeed();
	SVector2D velocity = desiredVelocity - mCharacter->velocity();
	if (dynamic_cast<Cow *>(mCharacter)){
		//printf("Seek velocity: %.f, %.f\n", velocity.x, velocity.y);
	}

	return velocity;
}

SVector2D SteeringBehaviors::flee(SVector2D targetPosition){
	const double panicDistanceSq = 300;
	if (dynamic_cast<Cow *>(mCharacter)){
		double distance = Vec2DDistance(mCharacter->position(), targetPosition);
		//printf("Distance: %.f\n", distance);
		//printf("Panic: %.f\n", panicDistanceSq);
	}
	if (Vec2DDistance(mCharacter->position(), targetPosition) > panicDistanceSq){
		return SVector2D(0,0);
	}

	SVector2D desiredVelocity = Vec2DNormalize(mCharacter->position() - targetPosition) * mCharacter->maxSpeed();
	SVector2D velocity = desiredVelocity - mCharacter->velocity();
	//printf("Flee velocity: %.f, %.f\n", velocity.x, velocity.y);
	return velocity;
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
	SVector2D ToPursuer = target->position() - mCharacter->position();

	double LookAheadTime = ToPursuer.Length() /
		(mCharacter->maxSpeed() + target->speed());

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
	//printf("Position: %.f, %.f\n", targetLocal.x, targetLocal.y);

	//project the target into world space
	SVector2D targetWorld = PointToWorldSpace(targetLocal, mCharacter->heading(), mCharacter->side(), mCharacter->position());

	//and steer towards it
	return targetWorld - mCharacter->position();
}
