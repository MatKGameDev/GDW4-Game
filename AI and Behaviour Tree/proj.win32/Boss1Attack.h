#pragma once
#include <math/Vec2.h>
#include <2d/CCSprite.h>
#include <2d/CCScene.h>


class Boss;

class Boss1LavaAttack
{
protected:
	Boss *bossPointer;


	Boss1LavaAttack(Boss *bossInstance);
public:
	virtual void update(const float &deltaT) = 0;
};

class LavaBall: public Boss1LavaAttack
{
public:
	LavaBall(const cocos2d::Vec2& heroPosition, Boss *bossInstance);
	~LavaBall();

	//Functions
	void update(const float &deltaT) override;
private:
	cocos2d::Sprite *ballSprite;
	cocos2d::Vec2 gravity, velocity, position;

	//Utility function
	float calculateAngle(const cocos2d::Vec2& heroPosition, const cocos2d::Vec2& bossMouthPosition, const float &velocity) const;
};

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

class SuckerBullet: public Boss1LavaAttack
{
public:
	SuckerBullet(const cocos2d::Vec2 &heroLocation, Boss *bossInstance);
	~SuckerBullet();
	void update(const float& deltaT) override;

private:
	cocos2d::Vec2 bulletVelocity, currentPosition, lastPosition, heroLocation;
	float traveledLength{0}, lengthVector{0};
	cocos2d::Sprite *bulletSprite;
};