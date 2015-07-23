#pragma once
#include "Character.h"
#include "Node.h"

class Bunny : public Character{
public:
	Bunny(SDL_Texture *texture, Node *startNode);
	~Bunny();
	void move();
};

