#ifndef __ASTAR__
#define __ASTAR__


#include "AStar.h"
#include "Node.h"
#include "AStarNode.h"
#include <vector>

using namespace std;

class AStar{
private:
	vector<AStarNode *> mOpenList = vector<AStarNode *>();
	vector<AStarNode *> mClosedList = vector<AStarNode *>();
	double DistanceBetween(Node *a, Node *b);

public:
	AStar(Node *startNode, Node *targetNode);
	~AStar();
	Node * getNextNode();
	bool isInOpenList(Node *node);
};


#endif
