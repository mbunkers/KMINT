#ifndef __Waypoint__
#define __Waypoint__

#include "IGameObject.h"
#include "Node.h"

class Waypoint : IGameObject{
private:
	int mDistance = 0;
	class Node *mFirstNode = nullptr;
	class Node *mSecondNode;
public:
	Waypoint(Node *node1, Node *node2, int distance);
	~Waypoint();
	int Distance();
	void Update(float dt);
	Node* OtherNode(Node *node);
};

#endif