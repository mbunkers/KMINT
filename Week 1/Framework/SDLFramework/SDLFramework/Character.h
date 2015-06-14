#pragma once

#include "IGameObject.h"

class Character : IGameObject{
public:
	Character(SDL_Texture *texture);
	~Character();

	void Draw();
	void Update(float deltaTime);
	void setNewPosition(int x, int y);
};

