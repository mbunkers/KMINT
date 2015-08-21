#ifndef __SEARCHSTATE__
#define __SEARCHSTATE__


#include "State.h"
class SearchState : public State{
public:
	SearchState();
	~SearchState();

	void Update();
	void Move(float deltaTime);
};

#endif
