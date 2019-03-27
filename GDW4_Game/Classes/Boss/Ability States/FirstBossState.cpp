#include "FirstBossState.h"
#include "Boss/General/Boss.h"
#include "FlameSplit.h"
#include "BossIdleState.h"
#include "FlameThrower.h"
#include "Boss/Attacks/Boss1Attack.h"
#include "Hero.h"
#include "ExplosiveBullet.h"

FirstBossSmallerState::FirstBossSmallerState(Boss* aBossInstance): bossPointer(aBossInstance)
{
}

FirstBossSmallerState::~FirstBossSmallerState()
{
}

/**
 * @brief This function updates the current state of the boss
 * Unless the function is overwritten, the smaller state will
 * do nothing
 */
void FirstBossSmallerState::update(float deltaT)
{/*Empty*/}

/**********************************************************************
 *
 *
 *                    Default Boss Attack State
 *
 *
 **********************************************************************/
FirstBossState::~FirstBossState()
{
	delete currentState;
}

void FirstBossState::setSmallerState(FirstBossSmallerState* newState)
{
	currentState = newState;
}

void FirstBossState::update(const float& deltaT, Boss* bossInstance)
{
}


//@brief Change to Idle state
void FirstBossState::changeToIdleState(Boss* boss)
{
	boss->setState(new Idling4FirstBoss(boss));
}

//@brief Change and perform Flame Split ability
void FirstBossState::changeToFlameSplit(Boss* boss)
{
	boss->setState(new FlameSplit4FirstBoss(boss));
}

void FirstBossState::changeToFlameThrower(Boss* boss)
{
	boss->setState(new FlameThrower4FirstBoss(boss));
}

void FirstBossState::changeToExplosiveBullet(Boss* boss)
{
	boss->setState(new ExplosiveBullet4FirstBoss(boss));
}






