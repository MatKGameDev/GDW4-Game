#include "FlameSplit.h"
#include "Boss/General/Boss.h"


FlameSplit4FirstBoss::FlameSplit4FirstBoss(Boss *boss)
	:FirstBossState(boss)
{
	//Prepare the animation
	const auto startingAction = cocos2d::Animate::create
	(
		cocos2d::AnimationCache::getInstance()->getAnimation("boss_spit_tell_PRE_animation_key")
	);

	const auto finishingAction = cocos2d::Animate::create
	(
		cocos2d::AnimationCache::getInstance()->getAnimation("boss_spit_tell_POST_animation_key")
	);

	//Set up the action for the boss
	boss->getSprite()->runAction
	(
		cocos2d::Sequence::create
		(
			cocos2d::Repeat::create(startingAction, 1),
			cocos2d::CallFunc::create([&] {bossPointer->spewLava(); }),
			cocos2d::DelayTime::create(2),
			cocos2d::Repeat::create(finishingAction, 1),
			cocos2d::CallFunc::create([&] {changeToIdleState(); }),
			nullptr
		)
	);
}

