#pragma once
#include "EmptyAttack.h"
#include "MeleeFireAttack.h"

enum HeroAttackTypes
{
	emptyA,
	meleeFireA
};

class HeroAttackManager
{
public:

	static EmptyAttack* empty;
	static MeleeFireAttack* meleeFire;

	static HeroAttackBase* currentAttack;

	static void setCurrentAttack(HeroAttackTypes attackType);
	static void update(float dt);
};