#pragma once
#include "EmptyAttack.h"
#include "MeleeFireAttack.h"
#include "ProjectileIceAttack.h"

enum HeroAttackTypes
{
	emptyA,
	meleeFireA,
	projectileIceA
};

class HeroAttackManager
{
public:

	static EmptyAttack* empty;
	static MeleeFireAttack* meleeFire;
	static ProjectileIceAttack* projectileIce;

	static HeroAttackBase* currentAttack;

	static void setCurrentAttack(HeroAttackTypes attackType, cocos2d::Scene* scene);
	static void update(float dt);
};