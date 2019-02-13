#pragma once
#include "cocos2d.h"

//forward declare some classes for member variable
class HeroIdle;
class HeroMoveLeft;
class HeroMoveRight;

enum HeroMoveStates
{
	idle,
	moveLeft,
	moveRight
};

class HeroMovementBase
{
public:
	static HeroIdle* idleState;
	static HeroMoveLeft* moveLeftState;
	static HeroMoveRight* moveRightState;

	static HeroMovementBase* currentState;
	static void setCurrentState(HeroMoveStates newState);

	virtual void init() {};
	virtual void update(float dt) {};
};