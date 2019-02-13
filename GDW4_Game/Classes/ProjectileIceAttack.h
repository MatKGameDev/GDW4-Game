#pragma once
#include "HeroAttackBase.h"

class ProjectileIceAttack : public HeroAttackBase
{
public:
	ProjectileIceAttack();

	void initAttack();
	void update(float dt);
};