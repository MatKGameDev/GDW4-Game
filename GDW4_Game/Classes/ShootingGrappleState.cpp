#include "ShootingGrappleState.h"
#include "Hero.h"
#include "Grapple.h"
#include "HeroStateManager.h"

ShootingGrappleState::ShootingGrappleState()
{
}

ShootingGrappleState::~ShootingGrappleState()
{
}

void ShootingGrappleState::onEnter()
{
	HeroStateManager::currentState = this;

	Hero::hero->sprite->stopAllActions();
}

void ShootingGrappleState::onExit()
{
	//determine which state to transition into
	if (Grapple::grapple->isActive)
		HeroStateManager::grappling->onEnter();
	
	else if (Hero::hero->velocity < 0)
		HeroStateManager::falling->onEnter();

	else if (Hero::hero->velocity > 0)
		HeroStateManager::jumping->onEnter();

	else if (Hero::hero->moveState != Hero::MoveDirection::idle)
		HeroStateManager::running->onEnter();

	else
		HeroStateManager::idle->onEnter();
}

void ShootingGrappleState::handleInput(InputType input)
{
	switch (input)
	{
	case InputType::p_space:
		Hero::hero->jump();
		break;
	}
}

void ShootingGrappleState::update(float dt)
{
	if (Hero::hero->moveState == Hero::MoveDirection::movingLeft)
		Hero::hero->moveLeft();
	else if (Hero::hero->moveState == Hero::MoveDirection::movingRight)
		Hero::hero->moveRight();

	if (Grapple::grapple->isLatched || !Grapple::grapple->isActive) //if the grapple latches onto something or becomes inactive (doesnt hit anything)
		onExit();
}
