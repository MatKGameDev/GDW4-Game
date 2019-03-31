#include "FlameThrower.h"
#include "Boss/General/Boss.h"

FlameThrower4FirstBoss::FlameThrower4FirstBoss(Boss *boss)
	: FirstBossState(boss)
{
	//Get the animation
	const auto startingAction = marcos::AnimationManager::getAnimation("boss_flame_tell_PRE_animation_key");
	const auto finishingAction = marcos::AnimationManager::getAnimation("boss_flame_tell_POST_animation_key");

	//Run the animation
	boss->getSprite()->runAction
	(
		cocos2d::Sequence::create
		(
			cocos2d::Repeat::create(startingAction, 1),
			cocos2d::CallFunc::create([&] {bossPointer->activateFlameThrower(); }),
			cocos2d::DelayTime::create(2.5f),
			cocos2d::Repeat::create(finishingAction, 1),
			cocos2d::CallFunc::create([&] {changeToIdleState(); }),
			nullptr
		)
	);
}
