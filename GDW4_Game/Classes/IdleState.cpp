#include "IdleState.h"
#include "Hero.h"
#include "HeroStateManager.h"

IdleState::IdleState()
{
}

IdleState::~IdleState()
{
}

void IdleState::onEnter()
{
	HeroStateManager::currentState = this;

	if (Hero::hero->lookState == Hero::LookDirection::lookingLeft)
	{
		auto anim = cocos2d::AnimationCache::getInstance()->getAnimation("idle_left_animation_key");
		auto action = cocos2d::Animate::create(anim);
		Hero::hero->sprite->stopAllActions();
		Hero::hero->sprite->runAction(cocos2d::RepeatForever::create(action->clone()));

	}
	else
	{
		auto anim = cocos2d::AnimationCache::getInstance()->getAnimation("idle_right_animation_key");
		auto action = cocos2d::Animate::create(anim);
		Hero::hero->sprite->stopAllActions();
		Hero::hero->sprite->runAction(cocos2d::RepeatForever::create(action->clone()));

	}
}

void IdleState::onExit()
{
	HeroStateManager::running->onEnter();
}

void IdleState::handleInput(InputType input)
{
	switch (input)
	{
	case InputType::p_space:
		HeroStateManager::jumping->onEnter();
		break;
	}
}

void IdleState::update(float dt)
{
	if (Hero::hero->moveState != Hero::MoveDirection::idle)
		onExit();
}