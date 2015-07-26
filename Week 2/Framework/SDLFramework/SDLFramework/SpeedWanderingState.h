#ifndef __SPEEDWANDERINGSTATE__
#define __SPEEDWANDERINGSTATE__

#include "State.h"
#include "Node.h"
class SpeedWanderingState : public State{
private:
	void moveOnce(Node *node);
public:
	SpeedWanderingState();
	~SpeedWanderingState();
	void Move();
};

#endif