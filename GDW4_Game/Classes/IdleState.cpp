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

	//get rid of this shit once we get separate animations for both sides and put them in the if statements
	auto anim = cocos2d::AnimationCache::getInstance()->getAnimation("idle_animation_key");
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