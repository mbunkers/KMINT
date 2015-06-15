#ifndef __Node__
#define __Node__

#include "IGameObject.h"
#include "Waypoint.h"
#include "Character.h"
#include <vector>
using namespace std;

class Node : IGameObject{
public:
	Node(int x, int y, int width, int height, SDL_Texture *texture);
	void Draw();
	void Update(float dt);
	void addNeighbour(Node *node, int value);
	int GetX();
	int GetY();
	vector<Character *> mCharacters = vector<Character *>();
	void setCharacter(Character *character);
	void removeCharacter(Character *character);
	vector<IGameObject *> mNeighbours;
	bool hasCharacter();
private:

};

#endif