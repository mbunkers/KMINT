#ifndef __SleepState__
#define __SleepState__

#include "State.h"
class SleepState :
	public State
{
public:
	SleepState();
	~SleepState();
	void Move(float deltaTime);
};

#endif