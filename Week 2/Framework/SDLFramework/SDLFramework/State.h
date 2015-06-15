#ifndef __STATE__
#define __STATE__

#include "Node.h"
#include "Character.h"

class State{
public:
	State();
	~State();

	class IGameObject *mTarget;
	class Character *mOwner;
	bool mFinished;

	virtual void Move();
	virtual void Update();

	void setTarget(Character *target);
};

#endif
