#include "EmptyAttack.h"

EmptyAttack::EmptyAttack() :
	onCooldown(false)
{
	hitbox = cocos2d::Rect::ZERO;
	attackTimer = 0.0f;
	attackCooldown = 0.0f;
}

void EmptyAttack::update(float dt)
{
	attackTimer += dt;
	if (attackTimer < attackCooldown)
		onCooldown = true;
	else
	{
		onCooldown = false;
		attackTimer = 0.0f;
		attackCooldown = 0.0f;
	}
}