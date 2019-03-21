#include "GrapplingState.h"
#include "Grapple.h"
#include "HeroStateManager.h"
#include "Hero.h"

GrapplingState::GrapplingState()
{
}

GrapplingState::~GrapplingState()
{
}

void GrapplingState::onEnter()
{
	HeroStateManager::currentState = this;

	if (Grapple::grapple->grappleTip.x < Hero::hero->getPosition().x) //hero should be facing left
	{
		auto anim = cocos2d::AnimationCache::getInstance()->getAnimation("grapple_left_animation_key");
		auto action = cocos2d::Animate::create(anim);
		Hero::hero->sprite->stopAllActions();
		Hero::hero->sprite->runAction(cocos2d::RepeatForever::create(action->clone()));

	}
	else //hero should be facing right
	{
		auto anim = cocos2d::AnimationCache::getInstance()->getAnimation("grapple_right_animation_key");
		auto action = cocos2d::Animate::create(anim);
		Hero::hero->sprite->stopAllActions();
		Hero::hero->sprite->runAction(cocos2d::RepeatForever::create(action->clone()));

	}
}

void GrapplingState::onExit()
{
	if (Grapple::grapple->isHeroAtEndPoint)
		HeroStateManager::holdingPlatform->onEnter();
	else if (!Grapple::grapple->isActive)
		HeroStateManager::falling->onEnter();
}

void GrapplingState::handleInput(InputType input)
{
}

void GrapplingState::update(float dt)
{
	if (Grapple::grapple->isHeroAtEndPoint || !Grapple::grapple->isActive)
		onExit();
}
