#pragma once

#include "IGameObject.h"
#include "Node.h"
#include "State.h"
#include <string>

using namespace std;

class Character : IGameObject{
public:
	Character(SDL_Texture *texture);
	~Character();

	class State *mCurrentState;
	class Node *mCurrentLocation;

	void Draw();
	void Update(float deltaTime);
	void setNewPosition(int x, int y);
	SDL_Texture *getTexture();
	string StateName();
};

