#include "Cow.h"

Cow::Cow(SDL_Texture *texture) : Character(texture){

}


Cow::~Cow(){
}

Node* Cow::moveToNextLocation(Node *startNode, Node *targetNode){
	reset(startNode, targetNode);
	return mAStar->getNextNode();
}

void Cow::reset(Node *startNode, Node *targetNode){
	delete mAStar;
	mAStar = new AStar(startNode, targetNode);
}
