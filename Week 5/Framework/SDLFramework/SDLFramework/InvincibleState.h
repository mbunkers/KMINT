#pragma once
#include "State.h"
class InvincibleState :
	public State {
public:
	InvincibleState();
	~InvincibleState();

	void Update();
};

