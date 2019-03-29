#pragma once
#include "Boss/Attacks/Boss1Attack.h"

class ExplosiveBullet : public Boss1LavaAttack
{
public:
	explicit ExplosiveBullet(const cocos2d::Vec2 &heroLocation, Boss *bossInstance);
	~ExplosiveBullet();

	//Member functions
	void update(const float& deltaT) override;

private:
	bool isWaiting{ true };
};