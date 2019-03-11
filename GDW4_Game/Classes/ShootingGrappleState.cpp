#include "ShootingGrappleState.h"
#include "Hero.h"
#include "Grapple.h"
#include "HeroStateManager.h"

ShootingGrappleState::ShootingGrappleState()
{
}

ShootingGrappleState::~ShootingGrappleState()
{
}

void ShootingGrappleState::onEnter()
{
	HeroStateManager::currentState = this;

	if (Hero::hero->lookState == Hero::LookDirection::lookingLeft)
	{
		auto anim = cocos2d::AnimationCache::getInstance()->getAnimation("shooting_grapple_left_animation_key");
		auto action = cocos2d::Animate::create(anim);
		Hero::hero->sprite->stopAllActions();
		Hero::hero->sprite->runAction(cocos2d::RepeatForever::create(action->clone()));

	}
	else
	{
		auto anim = cocos2d::AnimationCache::getInstance()->getAnimation("shooting_grapple_right_animation_key");
		auto action = cocos2d::Animate::create(anim);
		Hero::hero->sprite->stopAllActions();
		Hero::hero->sprite->runAction(cocos2d::RepeatForever::create(action->clone()));

	}
}

void ShootingGrappleState::onExit()
{
	//determine which state to transition into
	if (Grapple::grapple->isActive)
		HeroStateManager::grappling->onEnter();
	
	else if (Hero::hero->velocity < 0)
		HeroStateManager::falling->onEnter();

	else if (Hero::hero->velocity > 0)
		HeroStateManager::jumping->onEnter();

	else if (Hero::hero->moveState != Hero::MoveDirection::idle)
		HeroStateManager::running->onEnter();

	else
		HeroStateManager::idle->onEnter();
}

void ShootingGrappleState::handleInput(InputType input)
{
	switch (input)
	{
	case InputType::p_space:
		Hero::hero->jump();
		break;
	}
}

void ShootingGrappleState::update(float dt)
{
	if (Hero::hero->moveState == Hero::MoveDirection::movingLeft)
		Hero::hero->moveLeft();
	else if (Hero::hero->moveState == Hero::MoveDirection::movingRight)
		Hero::hero->moveRight();

	if (Grapple::grapple->isLatched || !Grapple::grapple->isActive) //if the grapple latches onto something or becomes inactive (doesnt hit anything)
		onExit();
}
