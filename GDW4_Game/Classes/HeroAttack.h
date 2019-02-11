#pragma once
#ifndef HERO_ATTACK_H
#define HERO_ATTACK_H

#include "cocos2d.h"

//class MeleeFireAttack;

class HeroAttack
{
public:
	//static MeleeFireAttack *meleeFire;

	bool isActive;
	float attackTimer;
	float attackDuration;
	float attackCooldown;
	cocos2d::Rect hitbox;

	virtual void update(float dt) {};
};

#endif