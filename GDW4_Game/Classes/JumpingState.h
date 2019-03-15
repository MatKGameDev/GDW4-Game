#pragma once
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

