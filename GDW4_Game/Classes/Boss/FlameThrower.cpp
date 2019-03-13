#include "FlameThrower.h"
#include "Boss.h"

void FlameThrowerCooldown::changeToIdle()
{
	bossPointer->getCurrentState()->changeToIdleState(bossPointer);
}

FlameThrowerCooldown::FlameThrowerCooldown(Boss* boss):FirstBossSmallerState(boss)
{
	auto action = cocos2d::Animate::create(cocos2d::AnimationCache::getInstance()->getAnimation("boss_flame_tell_POST_animation_key"));

	boss->getSprite()->runAction
	(
		cocos2d::Sequence::create
		(
			cocos2d::Repeat::create(action, 1),
			cocos2d::CallFunc::create([&] {this->changeToIdle(); }),
			nullptr
		)
	);
}

void FlameThrowerPerforming::ChangeToCooldown()
{
	bossPointer->getCurrentState()->setSmallerState(new FlameThrowerCooldown(bossPointer));
	delete this;
}

FlameThrowerPerforming::FlameThrowerPerforming(Boss* boss) :FirstBossSmallerState(boss), waitingTime(7.f)
{
	boss->activateFlameThrower();
}

void FlameThrowerPerforming::update(float deltaT)
{
	waitingTime -= deltaT;
	if (waitingTime <= 0)
		ChangeToCooldown();
}

void FlameThrowerCharging::ChangeToPerforming()
{
	bossPointer->getCurrentState()->setSmallerState(new FlameThrowerPerforming(bossPointer));
	delete this;
}

FlameThrowerCharging::FlameThrowerCharging(Boss* boss):FirstBossSmallerState(boss)
{
	auto action = cocos2d::Animate::create(cocos2d::AnimationCache::getInstance()->getAnimation("boss_flame_tell_PRE_animation_key"));
	boss->getSprite()->runAction
	(
		cocos2d::Sequence::create
		(
			cocos2d::Repeat::create(action, 1),
			cocos2d::CallFunc::create([&] {this->ChangeToPerforming(); }),
			nullptr
		)
	);
}

FlameThrower4FirstBoss::FlameThrower4FirstBoss(Boss *boss)
{
	currentState = new FlameThrowerCharging(boss);
}

void FlameThrower4FirstBoss::update(const float& deltaT, Boss* bossInstance)
{
	currentState->update(deltaT);
}
