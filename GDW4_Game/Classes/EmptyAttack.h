#pragma once
#ifndef EMPTYATTACK_H
#define EMPTYATTACK_H

#include "HeroAttackBase.h"

class EmptyAttack : public HeroAttackBase
{
public:
	EmptyAttack();

	bool onCooldown;

	void update(float dt);
};
#endif