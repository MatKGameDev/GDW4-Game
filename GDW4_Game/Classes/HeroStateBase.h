#pragma once
#include "InputType.h"
#include "cocos2d.h"

class HeroStateBase
{
public:
	HeroStateBase();
	~HeroStateBase();

	virtual void onEnter() = 0;
	virtual void onExit() = 0;
	virtual void handleInput(InputType input) = 0;
	virtual void update(float dt) = 0;
};