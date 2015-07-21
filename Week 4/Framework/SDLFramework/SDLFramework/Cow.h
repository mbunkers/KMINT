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

	
	Node *moveToNextLocation(Node *startNode, Node *targetNode);
	void move();
	void Update(float dt);
	void changeTarget(Character *target);
	void changeTarget(Cow *target);
	void reset(Node *startNode, Node *targetNode);
	void changeState();
	void sleep();
	void wakeup();

	AStar *mAStar;
};

#endif

