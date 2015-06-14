#pragma once
#include "Character.h"
#include "Node.h"
#include "AStar.h"

class Cow : public Character{
public:
	Cow(SDL_Texture *texture);
	~Cow();

	Node *mCurrentLocation;
	Node *moveToNextLocation();

	void reset(Node *startNode, Node *targetNode);

	AStar *mAStar;
};

