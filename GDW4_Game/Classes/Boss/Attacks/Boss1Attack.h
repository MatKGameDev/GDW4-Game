#pragma once
//Header files
#include <math/Vec2.h>
#include <2d/CCSprite.h>


//Foward declare classes
class Boss;
class HitBox;

class Boss1LavaAttack
{
protected:
	//Protected Variables
	Boss *bossPointer;
	cocos2d::Vec2 position, velocity, acceleration;
	cocos2d::Sprite *sprite;
	HitBox *hitBox;

	//Protected Constructor
	Boss1LavaAttack(Boss *bossInstance, const std::string fileName);
public:
	virtual ~Boss1LavaAttack();

	//Pure virtual function
	virtual void update(const float &deltaT) = 0;
	//Getters
	cocos2d::Rect getHitBox() const;

};

/*
 * @brief
 */
class LavaBall: public Boss1LavaAttack
{
public:
	LavaBall(int order, Boss *bossInstance);
	~LavaBall();

	//Functions
	void update(const float &deltaT) override;
private:
	float waitingTime;
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

class ExplosionArea :public Boss1LavaAttack
{
	float onTime;
public:
	explicit ExplosionArea(cocos2d::Vec2 &startPos, Boss *bossInstance);
	~ExplosionArea();

	//Member functions
	void update(const float& deltaT) override;
};

class ExplosiveBullet: public Boss1LavaAttack
{
public:
	explicit ExplosiveBullet(const cocos2d::Vec2 &heroLocation, Boss *bossInstance);
	~ExplosiveBullet();

	//Member functions
	void update(const float& deltaT) override;

private:
	cocos2d::Vec2 bulletVelocity, currentPosition, lastPosition, heroLocation;
	float traveledLength{0}, lengthVector{0};
};

