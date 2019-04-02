#pragma once
#ifndef DYINGSTATE_H	
#define DYINGSTATE_H

#include "HeroStateBase.h"

class DyingState : public HeroStateBase
{
public:
	DyingState();
	~DyingState();

	void onEnter();
	void onExit();
	void handleInput(InputType input);

	void update(float dt);
};
#endif