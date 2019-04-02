#include "AttackingState.h"
#include "HeroAttackManager.h"
#include "HeroStateManager.h"
#include "Hero.h"
#include "Grapple.h"


AttackingState::AttackingState()
{
}


AttackingState::~AttackingState()
{
}

void AttackingState::onEnter()
{
	HeroStateManager::currentState = this;

	Hero::hero->sprite->stopAllActions();
}

void AttackingState::onExit()
{
	//check which state to go to next from the top to the bottom of the hierarchy
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

//handle any input that occurs in this state
void AttackingState::handleInput(InputType input)
{
	switch (input)
	{
	case InputType::p_space:
		Hero::hero->jump();
		break;

	case InputType::r_space:
		//variable jump height
		Hero::hero->velocity.y /= 1.5;
		break;
	}
}

void AttackingState::update(float dt)
{
	if (Hero::hero->moveState == Hero::MoveDirection::movingLeft)
		Hero::hero->moveLeft();
	else if (Hero::hero->moveState == Hero::MoveDirection::movingRight)
		Hero::hero->moveRight();

	//if the attack ends, move onto another state
	if (HeroAttackManager::currentAttack == HeroAttackManager::empty)
		onExit();
}