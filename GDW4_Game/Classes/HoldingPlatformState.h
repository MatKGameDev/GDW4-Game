#pragma once
#include "HeroStateBase.h"

class HoldingPlatformState : public HeroStateBase
{
public:
	HoldingPlatformState();
	~HoldingPlatformState();

	void onEnter();
	void onExit();
	void handleInput(InputType input);
	void update(float dt);
};