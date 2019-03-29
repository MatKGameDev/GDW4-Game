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
	Boss1LavaAttack(Boss *bossInstance, const std::string& fileName);
public:
	virtual ~Boss1LavaAttack();

	//Pure virtual function
	virtual void update(const float &deltaT) = 0;
	//Getters
	cocos2d::Rect getHitBox() const;

};



