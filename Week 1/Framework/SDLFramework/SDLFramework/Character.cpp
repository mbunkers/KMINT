#include "Character.h"


Character::Character(SDL_Texture *texture){
	SetTexture(texture);
	SetSize(70, 70);
}

Character::~Character(){
}

void Character::Draw(){
	IGameObject::Draw();
}

SDL_Texture * Character::getTexture(){
	return GetTexture();
}

void Character::Update(float deltaTime){
	//IGameObject::Update(deltaTime);
}

void Character::setNewPosition(int x, int y){
	SetOffset(x, y);
}

string Character::StateName(){
	if (mCurrentState == nullptr){
		return "Onbekende staat";
	}
	return mCurrentState->name();
}
