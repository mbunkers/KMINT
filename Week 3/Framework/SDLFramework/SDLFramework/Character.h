#ifndef __CHARACTER__
#define __CHARACTER__


#include "IGameObject.h"
#include "Node.h"
#include "State.h"
#include "Item.h"
#include <string>

using namespace std;

class Character : IGameObject{
public:
	Character(SDL_Texture *texture);
	~Character();

	class State *mCurrentState;
	class Node *mCurrentLocation;
	class Item *mItem = nullptr;

	void respawn();

	void Draw();
	void Update(float deltaTime);
	void setNewPosition(int x, int y);
	SDL_Texture *getTexture();
	virtual void changeState();
	void sleep();
	void wander();
	void flee();
	void wakeup();
	void wakeup(Character *target);
	void search(class Item *item, int r, int g, int b);
	void chase(Character *target);
	string StateName();
};

#endif
