#pragma once
#include "FirstBossState.h"

class FlameThrowerCooldown : public FirstBossSmallerState
{
	void changeToIdle();
public:
	FlameThrowerCooldown(Boss *boss);
};

class FlameThrowerPerforming : public FirstBossSmallerState
{
	void ChangeToCooldown();
	float waitingTime;
public:
	FlameThrowerPerforming(Boss *boss);
	void update(float deltaT) override;
};

class FlameThrowerCharging : public FirstBossSmallerState
{
	void ChangeToPerforming();
public:
	FlameThrowerCharging(Boss *boss);
};


class FlameThrower4FirstBoss : public FirstBossState
{
public:
	FlameThrower4FirstBoss(Boss *boss);

	void update(const float& deltaT, Boss* bossInstance) override;
private:
};

