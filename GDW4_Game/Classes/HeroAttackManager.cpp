#include "HeroAttackManager.h"

EmptyAttack* HeroAttackManager::empty = new EmptyAttack();
MeleeFireAttack* HeroAttackManager::meleeFire = new MeleeFireAttack();
ProjectileIceAttack* HeroAttackManager::projectileIce = new ProjectileIceAttack();

HeroAttackBase* HeroAttackManager::currentAttack = new EmptyAttack();

void HeroAttackManager::setCurrentAttack(HeroAttackTypes attackType)
{
	//check which attack type to set and call init function if applicable
	switch (attackType)
	{
	case emptyA:
		currentAttack = empty;
		break;

	case meleeFireA:
		currentAttack = meleeFire;
		meleeFire->initAttack();
		break;

	case projectileIceA:
		currentAttack = projectileIce;
		projectileIce->initAttack();
		break;
	}
}

void HeroAttackManager::update(float dt)
{
	currentAttack->update(dt);
}