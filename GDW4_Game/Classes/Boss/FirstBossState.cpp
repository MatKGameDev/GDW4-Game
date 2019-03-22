#include "FirstBossState.h"
#include "Boss.h"
#include "FlameSplit.h"
#include "BossIdleState.h"
#include "FlameThrower.h"

FirstBossSmallerState::FirstBossSmallerState(Boss* aBossInstance): bossPointer(aBossInstance)
{
}

FirstBossSmallerState::~FirstBossSmallerState()
{
}

void FirstBossSmallerState::update(float deltaT)
{
}

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






