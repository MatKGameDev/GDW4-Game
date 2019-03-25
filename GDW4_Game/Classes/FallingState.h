#pragma once
#ifndef FALLINGSTATE_H
#define FALLINGSTATE_H

#include "HeroStateBase.h"

class FallingState : HeroStateBase
{
public:
	FallingState();
	~FallingState();

	void onEnter();
	void onExit();
	void handleInput(InputType input);
	void update(float dt);
};
#endif