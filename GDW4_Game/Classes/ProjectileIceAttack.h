#pragma once
#include "HeroAttackBase.h"

class ProjectileIceAttack : public HeroAttackBase
{
public:
	ProjectileIceAttack();

	void initAttack(cocos2d::Scene* scene);
	void update(float dt);
};