#include "Boss1Attack.h"
#include <cmath>
#include <base/CCDirector.h>
#include "Boss.h"

Boss1LavaAttack::Boss1LavaAttack(Boss* bossInstance) : bossPointer(bossInstance), hitBoxShape(cocos2d::DrawNode::create())
{
	cocos2d::Director::getInstance()->getRunningScene()->addChild(hitBoxShape);
}

void Boss1LavaAttack::redrawHitBox()
{
	//Change the hit box
	hitBox.setRect(position.x - width / 2, position.y - height / 2, width, height);

	//redraw the hit box
	hitBoxShape->clear();
	hitBoxShape->drawRect(cocos2d::Vec2(hitBox.getMinX(), hitBox.getMinY()), cocos2d::Vec2(hitBox.getMaxX(), hitBox.getMaxY()), cocos2d::Color4F(0.0f, 1.0f, 0.0f, 1.0f));
}

Boss1LavaAttack::~Boss1LavaAttack()
{
	cocos2d::Director::getInstance()->getRunningScene()->removeChild(hitBoxShape);
}


cocos2d::Rect Boss1LavaAttack::getHitBox() const
{
	return hitBox;
}

LavaBall::LavaBall(const cocos2d::Vec2& heroPosition, int order, Boss *bossInstance)
	: Boss1LavaAttack(bossInstance)
{
	sprite = cocos2d::Sprite::create("LavaBall.png");

	switch (order)
	{
	case 1:
		waitingTime = 1.5;
		position = cocos2d::Vec2(250, 500);
		break;
	case 2:
		waitingTime = 2.0;
		position = cocos2d::Vec2(250, 250);
		break;
	case 3:
		waitingTime = 2.5;
		position = cocos2d::Vec2(250, 750);
		break;
	default:
		throw;
	}

	//Set Position for the lava ball
	sprite->setPosition(position);
	cocos2d::Director::getInstance()->getRunningScene()->addChild(sprite);

	//Set physic variables
	acceleration.set(1250, 0);
	velocity.set(500, 0);

	//Set sprite size
	height = 50;
	width = 50;
}

LavaBall::~LavaBall()
{
	bossPointer->removeFromLavaList(this);
	cocos2d::Director::getInstance()->getRunningScene()->removeChild(sprite);
}

void LavaBall::update(const float& deltaT)
{
	if (waitingTime > 0)
	{
		waitingTime -= deltaT;

		//play some animation
	}
	else
	{
		velocity += acceleration * deltaT;
		position += velocity * deltaT;
		//Delete the object when it goes out of the screen
		if (position.x > 1920)
		{
			delete this;
			return;
		}
		sprite->setPosition(position);
		redrawHitBox();
	}
}



FlameThrower::FlameThrower(Boss *bossInstance) : Boss1LavaAttack(bossInstance), onTime(1.0f), drawNode(cocos2d::DrawNode::create())
{
	position.set(960, 500);
	sprite = cocos2d::Sprite::create("FlameThrower.png");
	sprite->setPosition(position);
	cocos2d::Director::getInstance()->getRunningScene()->addChild(sprite);

	//Setup hit box
	width = 1920;
	height = 450;
}

FlameThrower::~FlameThrower()
{
	bossPointer->removeFromLavaList(this);
	cocos2d::Director::getInstance()->getRunningScene()->removeChild(sprite);
}

void FlameThrower::update(const float& deltaT)
{
	if (waitingTime >= 0)
	{
		waitingTime -= deltaT;
	}
	else 
	{
		onTime -= deltaT;
		if (onTime <= 0) 
		{
			delete this;
			return;
		}
		redrawHitBox();
	}
}

SuckerBullet::SuckerBullet(const cocos2d::Vec2& heroLocation, Boss* bossInstance) : Boss1LavaAttack(bossInstance), currentPosition(bossInstance->getMouthPosition())
{
	//Set up the sprite
	sprite = cocos2d::Sprite::create("LavaBall.png");
	sprite->setPosition(bossInstance->getMouthPosition());
	cocos2d::Director::getInstance()->getRunningScene()->addChild(sprite);

	//set up the physics
	cocos2d::Vec2 tempVector = heroLocation - bossInstance->getMouthPosition();
	lengthVector = tempVector.getLength();
	bulletVelocity = tempVector.getNormalized() * 600;

	this->heroLocation = heroLocation;
}

SuckerBullet::~SuckerBullet()
{
	bossPointer->removeFromLavaList(this);
	cocos2d::Director::getInstance()->getRunningScene()->removeChild(sprite);
}

void SuckerBullet::update(const float& deltaT)
{
	lastPosition = currentPosition;
	currentPosition += bulletVelocity * deltaT;

	sprite->setPosition(currentPosition);

	traveledLength += (lastPosition - currentPosition).getLength();

	if (lengthVector <= traveledLength)
	{
		delete this;
	}
}
