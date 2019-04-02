#pragma once
#include "Boss/Attacks/Boss1Attack.h"

class FlameThrower : public Boss1LavaAttack
{
public:
	FlameThrower(Boss *bossInstance);
	~FlameThrower();
private:
	cocos2d::Vec2 startPoint;
};
