#include "Node.h"
#include "FWApplication.h"

Node::Node(int x, int y, int width, int height, SDL_Texture *texture){
	SetOffset(x, y);
	SetSize(width, height);
	SetTexture(texture);
	mNeighbours = vector<IGameObject *>();
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

	if (mCharacter != nullptr){
		mCharacter->Draw();
	}
}

int Node::GetX(){
	return mX;
}

int Node::GetY(){
	return mY;
}

void Node::addNeighbour(Node *node, int value){
	Waypoint *waypoint = new Waypoint(this, node, value);
	mNeighbours.push_back((IGameObject *)waypoint);
}

void Node::setCharacter(Character *character){
	mCharacter = character;
	mCharacter->setNewPosition(GetX(), GetY());
}
