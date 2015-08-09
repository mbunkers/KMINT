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
public:
	Cow(SDL_Texture *texture, Node *startNode);
	~Cow();

	void Update(float deltaTime);
	void respawn();
	void defaultState();
	void move();
	void changeTarget(Character *target);
	void changeTarget(Cow *target);
	void changeState();
};

#endif

