#ifndef __CHARACTER__
#define __CHARACTER__

#include "IGameObject.h"
#include "Node.h"
#include "State.h"
#include "Item.h"
#include "MovingEntity.h"
#include "SteeringBehaviors.h"
#include "SVector2D.h"

class Character : public MovingEntity{
private:
	double mTimeElapsed;
public:
	Character(SDL_Texture *texture);
	~Character();

	class SteeringBehaviors *mSteering;
	double timeElapsed()const{ return mTimeElapsed; }

	class State *mCurrentState;
	class Node *mCurrentLocation;
	class Item *mItem = nullptr;

	void defaultState();
	void respawn();

	void Draw();
	void Update(float deltaTime);
	SVector2D position();
	void setNewPosition(int x, int y);
	void setPosition(SVector2D position);
	SDL_Texture *getTexture();
	virtual void changeState();
	void sleep();
	void wander();
	void flee();
	void wakeup();
	void wakeup(Character *target);
	void search(class Item *item, int r, int g, int b);
	void chase(Character *target);

	void speedUp();
	void speedDown();
};

#endif
