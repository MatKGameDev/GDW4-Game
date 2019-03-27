#include "ExplosiveBullet.h"
#include "Boss/General/Boss.h"


void ExplosiveBulletCooldown::changeToIdle()
{
	bossPointer->getCurrentState()->changeToIdleState(bossPointer);
}

ExplosiveBulletCooldown::ExplosiveBulletCooldown(Boss* boss)
	:FirstBossSmallerState(boss)
{
	//Play some animation
}

ExplosiveBulletPerforming::ExplosiveBulletPerforming(Boss* boss)
	: FirstBossSmallerState(boss)
{
	bossPointer->shootSucker();
}

void ExplosiveBulletCharging::changeToPerforming()
{
	bossPointer->getCurrentState()->setSmallerState(new ExplosiveBulletPerforming(bossPointer));
	delete this;
}

ExplosiveBulletCharging::ExplosiveBulletCharging(Boss* boss)
	: FirstBossSmallerState(boss)
{
	
}

ExplosiveBullet4FirstBoss::ExplosiveBullet4FirstBoss(Boss* boss)
{
	boss->getSprite()->stopAllActions();
	currentState = new ExplosiveBulletCharging(boss);
}

void ExplosiveBullet4FirstBoss::update(const float& deltaT, Boss* bossInstance)
{
	currentState->update(deltaT);
}
