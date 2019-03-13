#include "BossIdleState.h"
#include "Boss.h"

Idling4FirstBoss::Idling4FirstBoss(Boss *boss) : cooldownBeforeNextAbility{ 5.f }
{
	auto action = cocos2d::Animate::create(cocos2d::AnimationCache::getInstance()->getAnimation("boss_idle_animation_key"));
	boss->getSprite()->runAction(cocos2d::RepeatForever::create(action));
}

void Idling4FirstBoss::update(const float &deltaT, Boss *bossInstance)
{
	cooldownBeforeNextAbility -= deltaT;
	//Play some animation

	if (cooldownBeforeNextAbility <= 0)
	{
		//chooseRandomAbility(bossInstance);
		changeToFlameSplit(bossInstance);
	}
}

void Idling4FirstBoss::chooseRandomAbility(Boss *bossInstance)
{
	//const int randomNum = cocos2d::RandomHelper::random_int(1, 3);
	switch (cocos2d::RandomHelper::random_int(1, 3))
	{
	case 1:
		changeToFlameThrower(bossInstance);
		break;
	case 2:
		changeToFlameSplit(bossInstance);
		break;
	case 3:
		//changeToSuckingBullet(bossInstance);
		break;
	default:
		throw;
	}
}