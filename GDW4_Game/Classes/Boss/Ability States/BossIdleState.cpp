#include "BossIdleState.h"
#include "Boss/General/Boss.h"

//Static function initialize
int Idling4FirstBoss::numberOfCast = 0;
const int Idling4FirstBoss::maxNumberOfCastPerRound = 7;

Idling4FirstBoss::Idling4FirstBoss(Boss *boss)
	: FirstBossState(boss), cooldownBeforeNextAbility{ 2.5f }
{
	//Get the animation
	const auto animationForIdling = marcos::AnimationManager::getAnimation("boss_idle_animation_key");

	//Run the animation
	boss->getSprite()->stopAllActions();
	boss->getSprite()->runAction(cocos2d::RepeatForever::create(animationForIdling));
}

/**
 * @brief Delete number of cast to 0
 */
Idling4FirstBoss::~Idling4FirstBoss()
{
}

/**
 * @brief Updates the idling time. When the time reaches
 * 0, the boss will perform an ability
 * 
 * @param deltaT The change of time from last frame to current
 * frame
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
	const int randomNum = cocos2d::RandomHelper::random_int(1, 20);

	if (randomNum >= 1 && randomNum <= 5)
		changeToExplosiveBullet();
	else if (randomNum >= 6 && randomNum <= 14)
		changeToFlameSplit();
	else
		changeToFlameThrower();

}