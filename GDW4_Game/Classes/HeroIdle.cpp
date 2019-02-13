#include "HeroIdle.h"
#include "Hero.h"
#include "cocos2d.h"

HeroIdle::HeroIdle()
{
	auto anim = cocos2d::AnimationCache::getInstance()->getAnimation("running_animation_key");
	auto action = cocos2d::Animate::create(anim);
	Hero::hero->sprite->runAction(cocos2d::RepeatForever::create(action));
}