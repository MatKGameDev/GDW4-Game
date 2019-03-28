#pragma once
#ifndef JUMPINGSTATE_H
#define JUMPINGSTATE_H

#include "HeroStateBase.h"
class JumpingState : public HeroStateBase
{
public:
	JumpingState();
	~JumpingState();

	void onEnter();
	void onExit();
	void handleInput(InputType input);

	void update(float dt);
};
#endif