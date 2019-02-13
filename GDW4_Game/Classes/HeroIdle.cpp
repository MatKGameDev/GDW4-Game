#include "HeroIdle.h"
#include "Hero.h"
#include "cocos2d.h"

HeroIdle::HeroIdle()
{
}

void HeroIdle::init()
{
	if (Hero::hero->sprite->isFlippedX())
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