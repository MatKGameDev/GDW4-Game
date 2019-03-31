#pragma once
#include "Boss/Attacks/Boss1Attack.h"
#include "Vect2.h"

/**
 * @brief This attack will spawn when the explosive bullet get deleted and 
 * will suck the player in (if they are in range).\n 
 * This object can only be created through Explosive bullet class
 */
class ExplosiveArea : public Boss1LavaAttack
{
public:
	//Constructors and Destructor
	~ExplosiveArea();

	//Member functions
	void update(const float& deltaT) override;
private:
	//Friend class
	friend class ExplosiveBullet;

	//Private constructor
	explicit ExplosiveArea(const cocos2d::Vec2 &startPosition, Boss *bossInstance);

	//Utility function
	void addForceToHero() const;
	Vect2 calculateDirectionToHero() const;
	void resetHeroForce() const;
	bool isHeroInRange() const;

	//Private data members
	mutable bool appliedForce;
};

/**
 * @brief This attack will be shot from the boss's mouth to the player
 * location.\n
 * This object will be destroyed if it collides with the player or 
 * ground objects
 */
class ExplosiveBullet : public Boss1LavaAttack
{
public:
	//Constructors and Destructor
	explicit ExplosiveBullet(const cocos2d::Vec2 &heroLocation, Boss *bossInstance);
	~ExplosiveBullet();

	//Member functions
	void update(const float& deltaT) override;
	void hitByHero() override;
	void hitByEnvironment() override;
private:
	//Private members
	bool isWaiting{ true };

	//Utility functions
	void setUpPhysic(const cocos2d::Vec2& heroPos);
};