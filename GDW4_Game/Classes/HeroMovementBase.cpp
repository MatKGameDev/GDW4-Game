#include "HeroMovementBase.h"
#include "HeroIdle.h"
#include "HeroMoveLeft.h"
#include "HeroMoveRight.h"

HeroIdle* HeroMovementBase::idleState = new HeroIdle();
HeroMoveLeft* HeroMovementBase::moveLeftState = new HeroMoveLeft();
HeroMoveRight* HeroMovementBase::moveRightState = new HeroMoveRight();

HeroMovementBase* HeroMovementBase::currentState = HeroMovementBase::idleState; //initialize state to idle

void HeroMovementBase::setCurrentState(HeroMoveStates newState)
{
	//check which movement type to set and call init function if applicable
	switch (newState)
	{
	case idle:
		currentState = idleState;
		break;

	case moveLeft:
		currentState = moveLeftState;
		moveLeftState->init();
		break;

	case moveRight:
		currentState = moveRightState;
		moveRightState->init();
		break;
	}
}