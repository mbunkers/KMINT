#include "Cow.h"

Cow::Cow(SDL_Texture *texture) : Character(texture){

}


Cow::~Cow(){
}

Node* Cow::moveToNextLocation(){
	return mAStar->getNextNode();
}

void Cow::reset(Node *startNode, Node *targetNode){
	delete mAStar;
	//mAStar = new AStar(startNode, targetNode);
}
