#ifndef __SEARCHSTATE__
#define __SEARCHSTATE__


#include "State.h"
class SearchState : public State{
public:
	SearchState();
	~SearchState();

	void Move();
};

#endif
