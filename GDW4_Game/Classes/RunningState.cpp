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

	//get rid of this shit once we get separate animations for both sides and put them in the if statements
	auto anim = cocos2d::AnimationCache::getInstance()->getAnimation("running_animation_key");
	auto action = cocos2d::Animate::create(anim);
	Hero::hero->sprite->stopAllActions();
	Hero::hero->sprite->setFlippedX(0);
	Hero::hero->sprite->runAction(cocos2d::RepeatForever::create(action->clone()));

	if (Hero::hero->lookingLeft)
	{
		//play left-looking animation

	}
	else
	{
		//play right-looking animation

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