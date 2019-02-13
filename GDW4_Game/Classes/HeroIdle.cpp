#include "HeroIdle.h"
#include "Hero.h"
#include "cocos2d.h"

HeroIdle::HeroIdle()
{
}

void HeroIdle::init()
{
	auto anim = cocos2d::AnimationCache::getInstance()->getAnimation("idle_animation_key");
	auto action = cocos2d::Animate::create(anim);
	Hero::hero->sprite->stopAllActions();
	Hero::hero->sprite->runAction(cocos2d::RepeatForever::create(action->clone()));
}