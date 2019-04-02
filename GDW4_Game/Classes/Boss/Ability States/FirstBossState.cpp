#include "FirstBossState.h"
#include "Boss/General/Boss.h"
#include "Boss/BossStates.h"

FirstBossState::FirstBossState(Boss *bossInstance)
	:bossPointer(bossInstance)
{
}

void FirstBossState::update(const float& deltaTime)
{
}

/**
 * @brief Change to idle state
 */
void FirstBossState::changeToIdleState() const
{
	bossPointer->setHitboxIndex(Boss::idling);
	bossPointer->setState(new Idling4FirstBoss(bossPointer));
}

/**
 * @brief Change to death state
 */
void FirstBossState::changeToDeathState() const
{
	bossPointer->setState(new DeathState(bossPointer));
}

/**
 * @brief Change to flame split state
 */
void FirstBossState::changeToFlameSplit() const
{
	bossPointer->setHitboxIndex(Boss::flameSplitter);
	bossPointer->setState(new FlameSplit4FirstBoss(bossPointer));
}

/**
 *@brief Change to flame thrower state
 */
void FirstBossState::changeToFlameThrower() const
{
	bossPointer->setHitboxIndex(Boss::flamethrower);
	bossPointer->setState(new FlameThrower4FirstBoss(bossPointer));
}

/**
 * @brief Change to explosive bullet state
 */
void FirstBossState::changeToExplosiveBullet() const
{
	bossPointer->setHitboxIndex(Boss::idling);
	bossPointer->setState(new ExplosiveBullet4FirstBoss(bossPointer));
}

/**
 * @brief Change to resting state
 */
void FirstBossState::changeToRestingState() const
{
	bossPointer->setHitboxIndex(Boss::idling);
	bossPointer->setState(new RestingState(bossPointer));
}
