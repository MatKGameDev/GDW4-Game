#include "FirstBossState.h"
#include "Boss/General/Boss.h"
#include "FlameSplit.h"
#include "BossIdleState.h"
#include "FlameThrower.h"
#include "ExplosiveBullet.h"


FirstBossState::FirstBossState(Boss *bossInstance)
	:bossPointer(bossInstance)
{
}

void FirstBossState::update(const float& deltaTime)
{
}


//@brief Change to Idle state
void FirstBossState::changeToIdleState()
{
	bossPointer->setState(new Idling4FirstBoss(bossPointer));
}



//@brief Change and perform Flame Split ability
void FirstBossState::changeToFlameSplit()
{
	bossPointer->setState(new FlameSplit4FirstBoss(bossPointer));
}

void FirstBossState::changeToFlameThrower()
{
	bossPointer->setState(new FlameThrower4FirstBoss(bossPointer));
}

void FirstBossState::changeToExplosiveBullet()
{
	bossPointer->setState(new ExplosiveBullet4FirstBoss(bossPointer));
}