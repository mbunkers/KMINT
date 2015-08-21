#include "Item.h"


Item::Item(SDL_Texture *texture){
	SetTexture(texture);
	SetSize(50, 50);
}


Item::~Item()
{
}

void Item::Draw(){
	IGameObject::Draw();
}

void Item::Update(float deltaTime){
	//IGameObject::Update(deltaTime);
}

void Item::setNewPosition(int x, int y){
	SetOffset(x, y);
}
