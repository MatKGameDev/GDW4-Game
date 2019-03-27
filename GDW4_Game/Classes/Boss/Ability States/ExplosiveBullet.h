#pragma once
#include "Boss/Ability States/FirstBossState.h"

class ExplosiveBulletCooldown: public FirstBossSmallerState
{
	void changeToIdle();
public:
	ExplosiveBulletCooldown(Boss *boss);
};

class ExplosiveBulletPerforming: public FirstBossSmallerState
{
	void changeToCooldown();
public:
	ExplosiveBulletPerforming(Boss *boss);
};

class ExplosiveBulletCharging: public FirstBossSmallerState
{
	void changeToPerforming();
public:
	ExplosiveBulletCharging(Boss *boss);
};

class ExplosiveBullet4FirstBoss: public FirstBossState
{
public:
	//Constructors and Destructor
	ExplosiveBullet4FirstBoss(Boss *boss);

	void update(const float& deltaT, Boss* bossInstance) override;
};
