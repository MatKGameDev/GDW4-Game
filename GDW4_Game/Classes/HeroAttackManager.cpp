#include "HeroAttackManager.h"
#include "HeroStateManager.h"

EmptyAttack* HeroAttackManager::empty = new EmptyAttack();
MeleeFireAttack* HeroAttackManager::meleeFire = new MeleeFireAttack();
ProjectileIceAttack* HeroAttackManager::projectileIce = new ProjectileIceAttack();

HeroAttackBase* HeroAttackManager::currentAttack = HeroAttackManager::empty; //initialize current to empty

void HeroAttackManager::setCurrentAttack(HeroAttackTypes attackType, cocos2d::Scene* scene)
{
	if (currentAttack == empty) //make sure there isnt already an attack in progress
	{
		HeroStateManager::attacking->onEnter();
		//check which attack type to set and call init function if applicable
		switch (attackType)
		{
		case meleeFireA:
			currentAttack = meleeFire;
			meleeFire->initAttack();
			break;

		case projectileIceA:
			currentAttack = projectileIce;
			projectileIce->initAttack(scene);
			break;
		}
	}
	else if (attackType == emptyA) //or if the attack is not empty but now being set to empty
		currentAttack = empty;
}

void HeroAttackManager::update(float dt)
{
	currentAttack->update(dt);
}