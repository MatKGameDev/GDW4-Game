#include "FallingState.h"
#include "HeroStateManager.h"
#include "Hero.h"
#include "Grapple.h"


FallingState::FallingState()
{
}

FallingState::~FallingState()
{
}

void FallingState::onEnter()
{
	HeroStateManager::currentState = this;
	Hero::hero->gravityMultiplier = 1.7f;

	Hero::hero->sprite->stopAllActions();
}

void FallingState::onExit()
{
	Hero::hero->gravityMultiplier = 1.0f;
	HeroStateManager::idle->onEnter();
}

void FallingState::handleInput(InputType input)
{
	switch (input)
	{
	case InputType::p_a:
		//if the hero is changing directions, call onEnter() again to play the proper animation
		if (Hero::hero->lookState == Hero::LookDirection::lookingRight)
		{
			Hero::hero->lookState = Hero::LookDirection::lookingLeft;
			onEnter();
		}
		break;

	case InputType::p_d:
		//if the hero is changing directions, call onEnter() again to play the proper animation
		if (Hero::hero->lookState == Hero::LookDirection::lookingLeft)
		{
			Hero::hero->lookState = Hero::LookDirection::lookingRight;
			onEnter();
		}
		break;
	}
}

void FallingState::update(float dt)
{
	if (Hero::hero->moveState == Hero::MoveDirection::movingLeft)
		Hero::hero->moveLeft();
	else if (Hero::hero->moveState == Hero::MoveDirection::movingRight)
		Hero::hero->moveRight();

	if (Hero::hero->velocity.y == 0)
		onExit();
}
