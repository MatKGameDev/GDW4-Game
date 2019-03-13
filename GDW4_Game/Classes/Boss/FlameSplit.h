#pragma once
#include "FirstBossState.h"


class FlameSplitCooldown : public FirstBossSmallerState
{
	void ChangeToIdle();
public:
	FlameSplitCooldown(Boss *boss);
};

class FlameSplitPerforming : public FirstBossSmallerState
{
	void ChangeToCooldown();
	float waitingTime;
public:
	FlameSplitPerforming(Boss *boss);
	void update(float deltaT) override;

};

/*
 *This class
 */
class FlameSplitCharging : public FirstBossSmallerState
{
	void changeToPerforming();
public:
	FlameSplitCharging(Boss *boss);

};



class FlameSplit4FirstBoss : public FirstBossState
{
public:
	FlameSplit4FirstBoss(Boss *boss);
	void update(const float &deltaT, Boss *bossInstance) override;

};