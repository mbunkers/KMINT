#ifndef __BUNNY__
#define __BUNNY__



#include "Character.h"
#include "Node.h"
#include "SVector2D.h"

class Bunny : public Character{
private:
	int mStateChangeCounter = 5;

	double mThreatRange = 200;
	double mSafeRange = mThreatRange * 2;

	bool isSafe(SVector2D distance);
	bool hasThreat(SVector2D distance);

public:
	Bunny(SDL_Texture *texture, Node *startNode);
	~Bunny();
	void move();
	void changeState();
	void flee();
	void Update(float deltaTime);
	double distanceToPersuer(SVector2D distanceVector);
};

#endif
