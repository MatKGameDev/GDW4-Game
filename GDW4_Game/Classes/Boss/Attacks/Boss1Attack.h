#pragma once
//Header files
#include <math/Vec2.h>
#include <2d/CCSprite.h>


//Foward declare classes
class Boss;
class HitBox;

/**
 * This class is the base class for all attacks for the boss.\n 
 * This class cannot be created by itself.
 */
class Boss1LavaAttack
{
public:
	enum BossAttack
	{
		ExplosiveBullet,
		Flamethrower,
		LavaBall
	};

	virtual ~Boss1LavaAttack();

	//Member functions
	virtual void update(const float &deltaT);
	virtual void hitByHero();
	virtual void hitByEnvironment();

	//Getters
	cocos2d::Rect getHitBox() const;
	BossAttack getAttackType() const;
	int getDealingDamage() const;

protected:
	//Protected Variables
	Boss *bossPointer;
	cocos2d::Vec2 position, velocity, acceleration;
	cocos2d::Sprite *sprite;
	HitBox *hitBox;
	BossAttack attackType;
	int dealingDamage{ 1 };

	//Protected Constructor
	Boss1LavaAttack(Boss *bossInstance, const std::string& fileName);
};



