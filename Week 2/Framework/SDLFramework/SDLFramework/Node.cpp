#include "Node.h"
#include "FWApplication.h"

Node::Node(int x, int y, int width, int height, SDL_Texture *texture){
	SetOffset(x, y);
	SetSize(width, height);
	SetTexture(texture);
	mNeighbours = vector<IGameObject *>();
	mCharacters = vector<Character *>();
}

void Node::Update(float dt){

}

void Node::Draw(){
	IGameObject::Draw();
	FWApplication::GetInstance()->SetColor(Color(0, 0, 0, 255));

	for (size_t i = 0; i < mNeighbours.size(); i++){
		Waypoint *waypoint = (Waypoint *)mNeighbours.at(i);
		Node *node = waypoint->OtherNode(this);
		FWApplication::GetInstance()->DrawLine(mX, mY, node->GetX(), node->GetY());
	}

	for (size_t i = 0; i < mCharacters.size(); i++){
		Character *character = mCharacters.at(i);
		character->Draw();
	}
}

int Node::GetX(){
	return mX;
}

int Node::GetY(){
	return mY;
}

bool Node::hasCharacter(){
	return mCharacters.size() > 0;
}

void Node::addNeighbour(Node *node, int value){
	Waypoint *waypoint = new Waypoint(this, node, value);
	mNeighbours.push_back((IGameObject *)waypoint);
	node->mNeighbours.push_back((IGameObject *)waypoint);
}

void Node::setCharacter(Character *character){
	character->setNewPosition(GetX(), GetY());
	mCharacters.push_back(character);
}

void Node::removeCharacter(Character *character){
	for (size_t i = 0; i < mCharacters.size(); i++){
		Character *testCharacter = mCharacters.at(i);
		if (character == testCharacter){
			mCharacters.erase(mCharacters.begin() + i);
			return;
		}
	}
}
