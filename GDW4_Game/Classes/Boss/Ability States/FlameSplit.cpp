#include "FlameSplit.h"
#include "Boss/General/Boss.h"

void FlameSplit4FirstBoss::performAction()
{
	something->spewLava();
}

void FlameSplit4FirstBoss::changeBackToIdling()
{
	changeToIdleState(something);
}


FlameSplit4FirstBoss::FlameSplit4FirstBoss(Boss *boss)
{
	something = boss;
	//Prepare the animation
	auto action = cocos2d::Animate::create(cocos2d::AnimationCache::getInstance()->getAnimation("boss_spit_tell_PRE_animation_key"));
	auto action2 = cocos2d::Animate::create(cocos2d::AnimationCache::getInstance()->getAnimation("boss_spit_tell_POST_animation_key"));

	//Set up the action for the boss
	boss->getSprite()->stopAllActions();
	boss->getSprite()->runAction
	(
		cocos2d::Sequence::create
		(
			cocos2d::Repeat::create(action, 1),
			cocos2d::CallFunc::create([&] {this->performAction(); }),
			cocos2d::DelayTime::create(3),
			cocos2d::Repeat::create(action2, 1),
			cocos2d::CallFunc::create([&] {this->changeBackToIdling(); }),
			nullptr
		)
	);
}

