#include "HeroMoveRight.h"
#include "Hero.h"

HeroMoveRight::HeroMoveRight()
{
}

void HeroMoveRight::init()
{
	auto anim = cocos2d::AnimationCache::getInstance()->getAnimation("running_animation_key");
	auto action = cocos2d::Animate::create(anim);
	Hero::hero->sprite->stopAllActions();
	Hero::hero->sprite->setFlippedX(0);
	Hero::hero->sprite->runAction(cocos2d::RepeatForever::create(action->clone()));
}

void HeroMoveRight::update(float dt)
{
	Hero::hero->moveRight();
}