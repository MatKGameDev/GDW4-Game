#include "HoldingPlatformState.h"
#include "Hero.h"
#include "HeroStateManager.h"
#include "Grapple.h"

HoldingPlatformState::HoldingPlatformState()
{
}

HoldingPlatformState::~HoldingPlatformState()
{
}

void HoldingPlatformState::onEnter()
{
	HeroStateManager::currentState = this;

	if (Hero::hero->lookState == Hero::LookDirection::lookingLeft)
	{
		auto anim = cocos2d::AnimationCache::getInstance()->getAnimation("grapple_hold_left_animation_key");
		auto action = cocos2d::Animate::create(anim);
		Hero::hero->sprite->stopAllActions();
		Hero::hero->sprite->runAction(cocos2d::RepeatForever::create(action->clone()));
	}
	else
	{
		auto anim = cocos2d::AnimationCache::getInstance()->getAnimation("grapple_hold_right_animation_key");
		auto action = cocos2d::Animate::create(anim);
		Hero::hero->sprite->stopAllActions();
		Hero::hero->sprite->runAction(cocos2d::RepeatForever::create(action->clone()));
	}
}

void HoldingPlatformState::onExit()
{
	HeroStateManager::falling->onEnter();
}

void HoldingPlatformState::handleInput(InputType input)
{
	switch (input)
	{
	case InputType::p_s: //let go of the platform and start falling down
		Grapple::grapple->unLatch();
		HeroStateManager::falling->onEnter();
		break;

	case InputType::p_space: //jump from the holding position
		HeroStateManager::grappleJumping->onEnter();
		break;
	}
}

void HoldingPlatformState::update(float dt)
{
	Hero::hero->velocity.y = 0;
	if (!Grapple::grapple->isActive)
		onExit();
}