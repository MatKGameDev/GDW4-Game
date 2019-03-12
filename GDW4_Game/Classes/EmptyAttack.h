#pragma once
#include "HeroAttackBase.h"

class EmptyAttack : public HeroAttackBase
{
public:
	EmptyAttack();

	bool onCooldown;

	void update(float dt);
};