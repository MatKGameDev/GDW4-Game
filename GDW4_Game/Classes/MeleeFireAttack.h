#pragma once
#include "HeroAttackBase.h"

class MeleeFireAttack : public HeroAttackBase
{
public:
	MeleeFireAttack();
	void initAttack();

	void attackUp();
	void attackDown();
	void attackLeft();
	void attackRight();
	void (MeleeFireAttack::*performAttack)(); //member function pointer.. syntax with these guys are weird

	void update(float dt);
};