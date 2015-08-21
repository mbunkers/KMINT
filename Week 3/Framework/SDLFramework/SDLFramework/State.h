#ifndef __STATE__
#define __STATE__

#include "Node.h"
#include "Character.h"
#include <string>

using namespace std;

class State{
private:
	string mName;
public:
	State(string name);
	~State();

	class IGameObject *mTarget;
	class Character *mOwner;
	bool mFinished;
	bool mMoveTarget = false;

	virtual void Move();
	virtual void Update();

	void setTarget(Character *target);
	virtual string name();
};

#endif
