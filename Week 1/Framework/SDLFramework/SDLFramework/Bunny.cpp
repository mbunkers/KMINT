#include "Bunny.h"


Bunny::Bunny(SDL_Texture *texture, Node *startNode) : Character(texture){
	mCurrentLocation = startNode;
}


Bunny::~Bunny()
{
}

void Bunny::move(){
}
