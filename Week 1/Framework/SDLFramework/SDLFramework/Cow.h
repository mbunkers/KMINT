#pragma once
#include "Character.h"
#include "Node.h"
#include "AStar.h"
#include "ChaseState.h"

class Cow : public Character{
public:
	Cow(SDL_Texture *texture, Node *startNode);
	~Cow();

	void move();
	void changeTarget(Character *target);
};

