#include "HeroAttackManager.h"
EmptyAttack* HeroAttackManager::empty = new EmptyAttack();
MeleeFireAttack* HeroAttackManager::meleeFire = new MeleeFireAttack();

HeroAttackBase* HeroAttackManager::currentAttack = new EmptyAttack();

void HeroAttackManager::setCurrentAttack(HeroAttackTypes attackType)
{
	switch (attackType)
	{
	case emptyA:
		currentAttack = empty;
		break;

	case meleeFireA:
		currentAttack = meleeFire;
		break;
	}
}

void HeroAttackManager::update(float dt)
{
	currentAttack->update(dt);
}