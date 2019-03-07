#pragma once
#include "HeroStateBase.h"
class RunningState : public HeroStateBase
{
public:
	RunningState();
	~RunningState();

	void onEnter();
	void onExit();
	void handleInput(InputType input);
	void update(float dt);
};