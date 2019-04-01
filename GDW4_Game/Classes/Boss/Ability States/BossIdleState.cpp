#include "BossIdleState.h"
#include "Boss/General/Boss.h"

//Static function initialize
int Idling4FirstBoss::numberOfCast = 0;
const int Idling4FirstBoss::maxNumberOfCastPerRound = 15;

Idling4FirstBoss::Idling4FirstBoss(Boss *boss)
	: FirstBossState(boss), cooldownBeforeNextAbility{ 1.f }
{
	//Get the animation
	const auto animationForIdling = marcos::AnimationManager::getAnimation("boss_idle_animation_key");

	//Run the animation
	boss->getSprite()->runAction(cocos2d::RepeatForever::create(animationForIdling));
}

/**
 * @brief Updates the idling time. When the time reaches
 * 0, the boss will perform an ability
 */
void Idling4FirstBoss::update(const float &deltaT)
{
	cooldownBeforeNextAbility -= deltaT;

	//Start shooting ability
	if (cooldownBeforeNextAbility <= 0)
	{
		bossPointer->getSprite()->stopAllActions();
		
		if (numberOfCast == maxNumberOfCastPerRound)
		{
			numberOfCast = 0;
			changeToRestingState();
		}
		else 
		{
			numberOfCast++;
			chooseRandomAbility();
		}
	}
}

/**
 * @brief Chooses a random ability to perform
 */
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
		changeToExplosiveBullet();
		break;
	default:
		throw;
	}
}