#include "DyingState.h"
#include "HeroStateManager.h"
#include "Hero.h"
#include "Grapple.h"

DyingState::DyingState()
{
}

DyingState::~DyingState()
{
}

void DyingState::onEnter()
{
	HeroStateManager::currentState = this;

	Hero::hero->sprite->stopAllActions();

	if (Hero::hero->lookState == Hero::LookDirection::lookingLeft)
	{
		auto anim = cocos2d::AnimationCache::getInstance()->getAnimation("hero_death_left_animation_key");
		auto action = cocos2d::Animate::create(anim);
		Hero::hero->sprite->stopAllActions();
		Hero::hero->sprite->runAction(cocos2d::Repeat::create(action->clone(), 1));
	}
	else //looking right
	{
		auto anim = cocos2d::AnimationCache::getInstance()->getAnimation("hero_death_right_animation_key");
		auto action = cocos2d::Animate::create(anim);
		Hero::hero->sprite->stopAllActions();
		Hero::hero->sprite->runAction(cocos2d::Repeat::create(action->clone(), 1));
	}
}

void DyingState::onExit()
{
}

void DyingState::handleInput(InputType input)
{
}

void DyingState::update(float dt)
{
	Grapple::grapple->indicator->setVisible(0);
	Hero::hero->force = Vect2(0.0f, 0.0f);
	Hero::hero->velocity = Vect2(0.0f, -400.0f);
}
