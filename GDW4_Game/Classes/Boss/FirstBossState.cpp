#include "FirstBossState.h"
#include "Boss.h"
#include "Boss1Attack.h"

FirstBossState::FirstBossState()
{
	currentState = new State;
}

FirstBossState::~FirstBossState()
{
	delete currentState;
}

//@brief Change to Idle state
void FirstBossState::changeToIdleState(Boss* boss)
{
	/*auto anim = cocos2d::AnimationCache::getInstance()->getAnimation("boss_idle_animation_key");
	auto action = cocos2d::Animate::create(anim);
	boss->getSprite()->stopAllActions();
	boss->getSprite()->runAction(cocos2d::RepeatForever::create(action->clone()));*/
	boss->setState(new Idling4FirstBoss);
}

//@brief Change and perform Flame Split ability
void FirstBossState::changeToFlameSplit(Boss* boss)
{
	auto anim = cocos2d::AnimationCache::getInstance()->getAnimation("boss_spit_tell_PRE_animation_key");
	auto action = cocos2d::Animate::create(anim);
	boss->getSprite()->stopAllActions();
	boss->getSprite()->runAction(cocos2d::Repeat::create(action->clone(), 1));
	boss->setState(new FlameSplit4FirstBoss);
}

//@brief Change to Flame Thrower ability
void FirstBossState::changeToFlameThrower(Boss* boss)
{
	auto anim = cocos2d::AnimationCache::getInstance()->getAnimation("boss_flame_tell_animation_key");
	auto action = cocos2d::Animate::create(anim);
	boss->getSprite()->stopAllActions();
	boss->getSprite()->runAction(cocos2d::Repeat::create(action->clone(), 1));
	boss->setState(new FlameThrower4FirstBoss);
}

//@brief Change to 
void FirstBossState::changeToSuckingBullet(Boss* boss)
{
	boss->setState(new SuckingAbility4FirstBoss);
}


Idling4FirstBoss::Idling4FirstBoss() : cooldownBeforeNextAbility{ 5.f }
{
	auto anim = cocos2d::AnimationCache::getInstance()->getAnimation("boss_flame_tell_animation_key");
	auto action = cocos2d::Animate::create(anim);
}

void Idling4FirstBoss::update(const float &deltaT, Boss *bossInstance)
{
	cooldownBeforeNextAbility -= deltaT;
	//Play some animation

	if (cooldownBeforeNextAbility <= 0)
	{
		chooseRandomAbility(bossInstance);
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
		changeToSuckingBullet(bossInstance);
		break;
	default:
		throw;
	}
}


FlameSplit4FirstBoss::FlameSplit4FirstBoss()
{
	*currentState = performingAbility;
}

void FlameSplit4FirstBoss::update(const float &deltaT, Boss *bossInstance)
{
	if (*currentState == charging)
	{
		//Add animation for the boss charging before shooting
	}
	else if (*currentState == performingAbility)
	{
		//Shoot a lava ball
		bossInstance->spewLava();

		//return to idle state
		changeToIdleState(bossInstance);
	}
}


FlameThrower4FirstBoss::FlameThrower4FirstBoss()
{
	*currentState = performingAbility;
}

void FlameThrower4FirstBoss::update(const float& deltaT, Boss* bossInstance)
{
	if (*currentState == charging)
	{

	}
	else if (*currentState == performingAbility)
	{
		bossInstance->activateFlameThrower();
		changeToIdleState(bossInstance);
	}
}

SuckingAbility4FirstBoss::SuckingAbility4FirstBoss()
{
	*currentState = performingAbility;
}

void SuckingAbility4FirstBoss::update(const float& deltaT, Boss* bossInstance)
{
	if (*currentState == charging)
	{

	}
	else if (*currentState == performingAbility)
	{
		bossInstance->shootSucker();
		changeToIdleState(bossInstance);
	}
}


