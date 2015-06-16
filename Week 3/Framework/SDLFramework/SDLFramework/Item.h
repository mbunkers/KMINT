#pragma once
#include "IGameObject.h"
class Item :
	public IGameObject
{
public:
	Item(SDL_Texture *texture);
	~Item();

	class Node *mCurrentLocation;

	void Draw();
	void Update(float deltaTime);
	void setNewPosition(int x, int y);
};

