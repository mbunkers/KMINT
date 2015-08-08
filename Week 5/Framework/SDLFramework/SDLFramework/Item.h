#ifndef __Item__
#define __Item__

#include "IGameObject.h"
class Item :
	public IGameObject
{
public:
	Item(SDL_Texture *texture);
	~Item();

	class Node *mCurrentLocation;
	bool mIsWeapon = false;

	void Draw();
	void Update(float deltaTime);
	void setNewPosition(int x, int y);
};

#endif