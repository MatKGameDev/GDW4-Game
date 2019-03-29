#include "BossIdleState.h"
#include "Boss/General/Boss.h"

Idling4FirstBoss::Idling4FirstBoss(Boss *boss)
	: FirstBossState(boss), cooldownBeforeNextAbility{ 5.f }
{
	const auto animationForIdling = cocos2d::Animate::create
	(
		cocos2d::AnimationCache::getInstance()->getAnimation("boss_idle_animation_key")
	);
	boss->getSprite()->runAction(cocos2d::RepeatForever::create(animationForIdling));
}

void Idling4FirstBoss::update(const float &deltaT)
{
	cooldownBeforeNextAbility -= deltaT;
	//Play some animation

	if (cooldownBeforeNextAbility <= 0)
	{
		bossPointer->getSprite()->stopAllActions();
		//chooseRandomAbility();
		changeToFlameThrower();
	}
}

void Idling4FirstBoss::chooseRandomAbility()
{
	switch (cocos2d::RandomHelper::random_int(1, 3))
	{
	case 1:
		changeToFlameThrower();
		break;
	case 2:
		changeToFlameSplit();
		break;
	case 3:
		//changeToExplosiveBullet(bossInstance);
		break;
	default:
		throw;
	}
}