#pragma once
#ifndef HEROSTATEBASE_H
#define HEROSTATEBASE_H

#include "InputType.h"
#include "cocos2d.h"
#include "ControllerInput.h"

class HeroStateBase
{
public:
	virtual void onEnter() = 0;
	virtual void onExit() = 0;
	virtual void handleInput(InputType input) = 0;
	virtual void update(float dt) = 0;
};
#endif