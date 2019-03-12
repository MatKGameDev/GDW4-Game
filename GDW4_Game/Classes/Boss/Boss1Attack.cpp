#include "Boss1Attack.h"
#include "Boss.h"

/********************************************************************************************************
 *
 *
 *										Boss Lava Attack Functions
 *
 *
 *******************************************************************************************************/

Boss1LavaAttack::Boss1LavaAttack(Boss* bossInstance) : bossPointer(bossInstance)
{
}

Boss1LavaAttack::~Boss1LavaAttack()
{
	delete hitBox;
}


cocos2d::Rect Boss1LavaAttack::getHitBox() const
{
	return hitBox->hitBox;
}


/********************************************************************************************************
 *
 *
 *										Lava Ball Functions
 *
 *
 *******************************************************************************************************/
LavaBall::LavaBall(int order, Boss *bossInstance)
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
	bossPointer->getBossScene()->addChild(sprite);

	//Set physic variables
	acceleration.set(1250, 0);
	velocity.set(500, 0);

	//Set sprite size
	hitBox = new HitBox(bossPointer->getBossScene(), 50.f, 50);
}

LavaBall::~LavaBall()
{
	bossPointer->removeFromLavaList(this);
	bossPointer->getBossScene()->removeChild(sprite);
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
		hitBox->updateHitBox(position);
	}
}

/********************************************************************************************************
 *
 *
 *										Flame Thrower Functions
 *
 *
 *******************************************************************************************************/

FlameThrower::FlameThrower(Boss *bossInstance) : Boss1LavaAttack(bossInstance), onTime(1.0f), drawNode(cocos2d::DrawNode::create())
{
	position.set(960, 500);
	sprite = cocos2d::Sprite::create("FlameThrower.png");
	sprite->setPosition(position);
	bossPointer->getBossScene()->addChild(sprite);

	//Setup hit box
	hitBox = new HitBox(bossPointer->getBossScene(), 450, 1920);
}

FlameThrower::~FlameThrower()
{
	bossPointer->removeFromLavaList(this);
	bossPointer->getBossScene()->removeChild(sprite);
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
		hitBox->updateHitBox(position);
	}
}


/********************************************************************************************************
 *
 *
 *										Sucking Bullet Functions
 *
 *
 *******************************************************************************************************/


SuckerBullet::SuckerBullet(const cocos2d::Vec2& heroLocation, Boss* bossInstance) : Boss1LavaAttack(bossInstance), currentPosition(bossInstance->getMouthPosition())
{
	//Set up the sprite
	sprite = cocos2d::Sprite::create("LavaBall.png");
	position.set(bossInstance->getMouthPosition());
	sprite->setPosition(position);
	bossPointer->getBossScene()->addChild(sprite);

	//Set up hit box
	hitBox = new HitBox(bossPointer->getBossScene(), 50.f, 50);

	//set up the physics
	cocos2d::Vec2 tempVector = heroLocation - bossInstance->getMouthPosition();
	lengthVector = tempVector.getLength();
	bulletVelocity = tempVector.getNormalized() * 600;

	this->heroLocation = heroLocation;
}

SuckerBullet::~SuckerBullet()
{
	bossPointer->removeFromLavaList(this);
	bossPointer->getBossScene()->removeChild(sprite);
}

void SuckerBullet::update(const float& deltaT)
{
	lastPosition = position;
	position += bulletVelocity * deltaT;

	sprite->setPosition(position);

	traveledLength += (lastPosition - position).getLength();

	if (lengthVector <= traveledLength)
	{
		delete this;
		return;
	}
	hitBox->updateHitBox(position);
}
