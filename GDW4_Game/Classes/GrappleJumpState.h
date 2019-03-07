#pragma once
#include "HeroStateBase.h"

class GrappleJumpState : public HeroStateBase
{
public:
	GrappleJumpState();
	~GrappleJumpState();

	void onEnter();
	void onExit();
	void handleInput(InputType input);
	void update(float dt);
};