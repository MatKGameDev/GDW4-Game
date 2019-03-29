#include "ExplosiveBullet.h"
#include "Boss/General/Boss.h"


ExplosiveBullet4FirstBoss::ExplosiveBullet4FirstBoss(Boss* boss)
	:FirstBossState(boss)
{
	//Get the animations ready
	const auto startingAnimation = cocos2d::Animate::create
	(
		cocos2d::AnimationCache::getInstance()->getAnimation("boss_explosive_tell_PRE_animation_key")
	);

	const auto finishingAnimation = cocos2d::Animate::create
	(
		cocos2d::AnimationCache::getInstance()->getAnimation("boss_explosive_tell_POST_animation_key")
	);

	//Play the animation
	bossPointer->getSprite()->runAction
	(
		cocos2d::Sequence::create
		(
			cocos2d::Repeat::create(startingAnimation, 1),
			cocos2d::CallFunc::create([&] {bossPointer->shootExplosiveBullet(); }),
			cocos2d::DelayTime::create(0.5),
			cocos2d::Repeat::create(finishingAnimation, 1),
			cocos2d::CallFunc::create([&] {changeToIdleState(); }),
			nullptr
		)
	);
}

