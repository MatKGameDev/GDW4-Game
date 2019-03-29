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
	if (Hero::hero->lookState == Hero::LookDirection::lookingLeft)
	{
		auto anim = cocos2d::AnimationCache::getInstance()->getAnimation("falling_left_animation_key");
		auto action = cocos2d::Animate::create(anim);
		Hero::hero->sprite->stopAllActions();
		Hero::hero->sprite->runAction(cocos2d::RepeatForever::create(action->clone()));

	}
	else
	{
		auto anim = cocos2d::AnimationCache::getInstance()->getAnimation("falling_right_animation_key");
		auto action = cocos2d::Animate::create(anim);
		Hero::hero->sprite->stopAllActions();
		Hero::hero->sprite->runAction(cocos2d::RepeatForever::create(action->clone()));

	}
}

void FallingState::onExit()
{
	if (Hero::hero->moveState == Hero::MoveDirection::idle)
		HeroStateManager::idle->onEnter();
	else //moving
		HeroStateManager::running->onEnter();
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

	case InputType::r_space:
		//variable jump height
		Hero::hero->velocity.y /= 1.5;
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
