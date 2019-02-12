#pragma once
#include "HeroAttackBase.h"

class EmptyAttack : public HeroAttackBase
{
public:
	EmptyAttack();

	void update(float dt);
};