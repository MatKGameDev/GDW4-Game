#pragma once
#ifndef MELEE_FIRE_ATTACK_H
#define MELEE_FIRE_ATTACK_H

#include "HeroAttack.h"

class MeleeFireAttack : public HeroAttack
{
public:
	MeleeFireAttack();
	//cocos2d::Rect hitbox;
	void update(float dt);
};

#endif