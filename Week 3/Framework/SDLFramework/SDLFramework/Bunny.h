#ifndef __BUNNY__
#define __BUNNY__



#include "Character.h"
#include "Node.h"

class Bunny : public Character{
private:
	int mStateChangeCounter = 5;
public:
	Bunny(SDL_Texture *texture, Node *startNode);
	~Bunny();
	void move();
	void changeState();
	void Update(float deltaTime);
};

#endif
