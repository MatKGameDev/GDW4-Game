#include "JumpingState.h"
#include "Hero.h"
#include "HeroStateManager.h"

JumpingState::JumpingState()
{
}


JumpingState::~JumpingState()
{
}

void JumpingState::onEnter()
{
	HeroStateManager::currentState = this;

	if (Hero::hero->lookState == Hero::LookDirection::lookingLeft)
	{
		auto anim = cocos2d::AnimationCache::getInstance()->getAnimation("jumping_left_animation_key");
		auto action = cocos2d::Animate::create(anim);
		Hero::hero->sprite->stopAllActions();
		Hero::hero->sprite->runAction(cocos2d::RepeatForever::create(action->clone()));

	}
	else
	{
		auto anim = cocos2d::AnimationCache::getInstance()->getAnimation("jumping_right_animation_key");
		auto action = cocos2d::Animate::create(anim);
		Hero::hero->sprite->stopAllActions();
		Hero::hero->sprite->runAction(cocos2d::RepeatForever::create(action->clone()));

	}

	Hero::hero->jump();
}

void JumpingState::onExit()
{
	if (Hero::hero->velocity.y < 0)
		HeroStateManager::falling->onEnter();
	else if (Hero::hero->velocity.y == 0)
		HeroStateManager::idle->onEnter();
}

void JumpingState::handleInput(InputType input)
{
	switch (input)
	{	
	case InputType::r_space:
		//variable jump height
		Hero::hero->velocity.y /= 1.5;
		break;

	case InputType::p_a:
		//if the hero is changing directions, call onEnter() again to play the proper animation
		if (Hero::hero->lookState == Hero::LookDirection::lookingRight)
		{
			Hero::hero->lookState = Hero::LookDirection::lookingLeft;
			HeroStateManager::falling->onEnter();
		}
		break;

	case InputType::p_d:
		//if the hero is changing directions, call onEnter() again to play the proper animation
		if (Hero::hero->lookState == Hero::LookDirection::lookingLeft)
		{
			Hero::hero->lookState = Hero::LookDirection::lookingRight;
			HeroStateManager::falling->onEnter();
		}
	}
}

void JumpingState::update(float dt)
{
	if (Hero::hero->moveState == Hero::MoveDirection::movingLeft)
		Hero::hero->moveLeft();
	else if (Hero::hero->moveState == Hero::MoveDirection::movingRight)
		Hero::hero->moveRight();

	if (Hero::hero->velocity.y <= 0)
		onExit();
}
