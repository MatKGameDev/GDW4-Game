#pragma once
#include "HeroStateBase.h"

class IdleState : public HeroStateBase
{
public:
	IdleState();
	~IdleState();

	void onEnter();
	void onExit();
	void handleInput(InputType input);
	void update(float dt);
};