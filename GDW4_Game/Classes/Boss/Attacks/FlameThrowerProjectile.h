#pragma once
#include "Boss/Attacks/Boss1Attack.h"

class FlameThrower : public Boss1LavaAttack
{
public:
	FlameThrower(Boss *bossInstance);
	~FlameThrower();
	void update(const float& deltaT) override;
private:
	cocos2d::Vec2 startPoint;
	float onTime;
	cocos2d::DrawNode *drawNode;
};
