#include "RunningState.h"
#include "Hero.h"
#include "HeroStateManager.h"

RunningState::RunningState()
{
}

RunningState::~RunningState()
{
}

void RunningState::onEnter()
 {
	HeroStateManager::currentState = this;

	if (Hero::hero->lookState == Hero::LookDirection::lookingLeft)
	{
		auto anim = cocos2d::AnimationCache::getInstance()->getAnimation("running_left_animation_key");
		auto action = cocos2d::Animate::create(anim);
		Hero::hero->sprite->stopAllActions();
		Hero::hero->sprite->runAction(cocos2d::RepeatForever::create(action->clone()));

	}
	else
	{
		auto anim = cocos2d::AnimationCache::getInstance()->getAnimation("running_right_animation_key");
		auto action = cocos2d::Animate::create(anim);
		Hero::hero->sprite->stopAllActions();
		Hero::hero->sprite->runAction(cocos2d::RepeatForever::create(action->clone()));

	}
}

void RunningState::onExit()
{
	if (Hero::hero->velocity.y < 0)
		HeroStateManager::falling->onEnter();
	else
		HeroStateManager::idle->onEnter();
}

void RunningState::handleInput(InputType input)
{
	switch (input)
	{
	case InputType::p_space:
		HeroStateManager::jumping->onEnter();
		break;

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

void RunningState::update(float dt)
{
	switch (Hero::hero->moveState)
	{
	case Hero::MoveDirection::movingLeft:
		Hero::hero->moveLeft();
		break;

	case Hero::MoveDirection::movingRight:
		Hero::hero->moveRight();
		break;

	case Hero::MoveDirection::idle:
		onExit();
		break;
	}

	if (Hero::hero->velocity.y < 0)
		onExit();
}