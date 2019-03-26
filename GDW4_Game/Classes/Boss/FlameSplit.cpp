#include "FlameSplit.h"
#include "Boss.h"

void FlameSplitCooldown::ChangeToIdle()
{
	bossPointer->getCurrentState()->changeToIdleState(bossPointer);
}

FlameSplitCooldown::FlameSplitCooldown(Boss* boss) : FirstBossSmallerState(boss)
{
	auto action = cocos2d::Animate::create(cocos2d::AnimationCache::getInstance()->getAnimation("boss_spit_tell_POST_animation_key"));

	boss->getSprite()->runAction
	(
		cocos2d::Sequence::create
		(
			cocos2d::Repeat::create(action, 1),
			cocos2d::CallFunc::create([&] {this->ChangeToIdle(); }),
			nullptr
		)
	);
}

void FlameSplitPerforming::ChangeToCooldown()
{
	bossPointer->getCurrentState()->setSmallerState(new FlameSplitCooldown(bossPointer));
	delete this;
}


FlameSplitPerforming::FlameSplitPerforming(Boss* boss) : FirstBossSmallerState(boss), waitingTime(3)
{
	bossPointer->spewLava();
}

void FlameSplitPerforming::update(float deltaT)
{
	waitingTime -= deltaT;
	if (waitingTime <= 0)
		ChangeToCooldown();
}


void FlameSplitCharging::changeToPerforming()
{
	//Change to performing state
	bossPointer->getCurrentState()->setSmallerState(new FlameSplitPerforming(bossPointer));
	delete this;
}

FlameSplitCharging::FlameSplitCharging(Boss* boss) : FirstBossSmallerState(boss)
{
	auto action = cocos2d::Animate::create(cocos2d::AnimationCache::getInstance()->getAnimation("boss_spit_tell_PRE_animation_key"));

	boss->getSprite()->runAction
	(
		cocos2d::Sequence::create
		(
			cocos2d::Repeat::create(action, 1),
			cocos2d::CallFunc::create([&] {this->changeToPerforming(); }),
			nullptr
		)
	);
}


FlameSplit4FirstBoss::FlameSplit4FirstBoss(Boss *boss)
{
	boss->getSprite()->stopAllActions();
	currentState = new FlameSplitCharging(boss);
}

void FlameSplit4FirstBoss::update(const float &deltaT, Boss *bossInstance)
{
	currentState->update(deltaT);
}
