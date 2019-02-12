#pragma once
#include "HeroAttackBase.h"

class MeleeFireAttack : public HeroAttackBase
{
public:
	MeleeFireAttack();
	void update(float dt);
};