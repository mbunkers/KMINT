#ifndef __CHARACTER__
#define __CHARACTER__


#include "IGameObject.h"
#include "Node.h"
#include "State.h"
#include "Item.h"

class Character : IGameObject{
public:
	Character(SDL_Texture *texture);
	~Character();

	class State *mCurrentState;
	class Node *mCurrentLocation;
	class Item *mItem = nullptr;

	void Draw();
	void Update(float deltaTime);
	void setNewPosition(int x, int y);
	SDL_Texture *getTexture();
	virtual void changeState();
	virtual void sleep();
	virtual void flee();
	virtual void wakeup();
};

#endif
