#include "GrappleJumpState.h"
#include "Grapple.h"
#include "Hero.h"
#include "HeroStateManager.h"

GrappleJumpState::GrappleJumpState()
{
}


GrappleJumpState::~GrappleJumpState()
{
}

void GrappleJumpState::onEnter()
{
	HeroStateManager::currentState = this;

	Grapple::grapple->unLatch();
	Hero::hero->jump();

	Hero::hero->sprite->stopAllActions();
}

void GrappleJumpState::onExit()
{
	if (Hero::hero->velocity.y < 0)
		HeroStateManager::falling->onEnter();
	else if (Hero::hero->velocity.y == 0)
		HeroStateManager::idle->onEnter();
}

void GrappleJumpState::handleInput(InputType input)
{
	switch (input)
	{
	case InputType::r_space:
		//variable jump height
		Hero::hero->velocity.y /= 1.5;
		break;
	}
}

void GrappleJumpState::update(float dt)
{
	if (Hero::hero->moveState == Hero::MoveDirection::movingLeft)
		Hero::hero->moveLeft();
	else if (Hero::hero->moveState == Hero::MoveDirection::movingRight)
		Hero::hero->moveRight();

	if (Hero::hero->velocity.y <= 0)
		onExit();
}
