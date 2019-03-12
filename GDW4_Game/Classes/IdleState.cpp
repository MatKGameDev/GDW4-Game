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
		auto anim = cocos2d::AnimationCache::getInstance()->getAnimation("boss_spit_animation_key");
		auto action = cocos2d::Animate::create(anim);
		Hero::hero->sprite->stopAllActions();
		Hero::hero->sprite->runAction(cocos2d::Repeat::create(action->clone(),1));

	}
	else
	{
		auto anim = cocos2d::AnimationCache::getInstance()->getAnimation("boss_spit_tell_animation_key");
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