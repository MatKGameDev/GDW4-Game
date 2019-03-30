#pragma once
#include "Boss/Attacks/Boss1Attack.h"

class ExplosiveArea : public Boss1LavaAttack
{
public:
	explicit ExplosiveArea(const cocos2d::Vec2 &startPosition, Boss *bossInstance);
	~ExplosiveArea();

	void update(const float& deltaT) override;
};

class ExplosiveBullet : public Boss1LavaAttack
{
public:
	explicit ExplosiveBullet(const cocos2d::Vec2 &heroLocation, Boss *bossInstance);
	~ExplosiveBullet();

	//Member functions
	void update(const float& deltaT) override;
	void hitByHero() override;
	void hitByEnvironment() override;

private:
	//Private members
	bool isWaiting{ true };

	//Private member functions
	void setUpPhysic(const cocos2d::Vec2& heroPos);
};