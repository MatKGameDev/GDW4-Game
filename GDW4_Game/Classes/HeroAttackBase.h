#pragma once
#include "cocos2d.h"

class HeroAttackBase
{
public:
	float attackTimer;
	float attackWindup;
	float attackDuration;
	float attackCooldown;

	bool disabled;

	cocos2d::Rect hitbox;

	static bool isWKeyHeld;
	static bool isSKeyHeld;

	virtual void initAttack() {};
	virtual void update(float dt) {};
};