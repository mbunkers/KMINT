#pragma once
#include "State.h"
class HideState :
	public State {
public:
	HideState();
	~HideState();

	void Update();
};

