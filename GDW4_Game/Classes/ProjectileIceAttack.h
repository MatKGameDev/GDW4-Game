#pragma once
#ifndef PROJECTILEICEATTACK_H
#define PROJECTILEICEATTACK_H

#include "HeroAttackBase.h"

class ProjectileIceAttack : public HeroAttackBase
{
public:
	ProjectileIceAttack();

	void initAttack(cocos2d::Scene* scene);
	void update(float dt);
};
#endif