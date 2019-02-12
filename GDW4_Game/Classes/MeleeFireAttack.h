#pragma once
#include "HeroAttackBase.h"

class MeleeFireAttack : public HeroAttackBase
{
public:
	MeleeFireAttack();
	//cocos2d::Rect hitbox;
	void update(float dt);
};