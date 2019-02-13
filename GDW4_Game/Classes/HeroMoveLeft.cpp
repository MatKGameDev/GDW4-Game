#include "HeroMoveLeft.h"
#include "Hero.h"

HeroMoveLeft::HeroMoveLeft()
{
}

void HeroMoveLeft::init()
{
	auto anim = cocos2d::AnimationCache::getInstance()->getAnimation("running_animation_key");
	auto action = cocos2d::Animate::create(anim);
	Hero::hero->sprite->stopAllActions();
	Hero::hero->sprite->setFlippedX(1);
	Hero::hero->sprite->runAction(cocos2d::RepeatForever::create(action->clone()));
}

void HeroMoveLeft::update(float dt)
{
	Hero::hero->moveLeft();
}