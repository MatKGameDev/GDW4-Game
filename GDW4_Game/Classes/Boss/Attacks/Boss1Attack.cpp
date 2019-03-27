#include "Boss1Attack.h"
#include "Boss/General/Boss.h"
#include "Boss/General/HitBox.h"

/********************************************************************************************************
 *
 *
 *										Boss Lava Attack Functions
 *
 *
 *******************************************************************************************************/

Boss1LavaAttack::Boss1LavaAttack(Boss* bossInstance, const std::string fileName)
	: bossPointer(bossInstance), sprite(cocos2d::Sprite::create(fileName))
{
	bossPointer->getBossScene()->addChild(sprite, 18);
}

Boss1LavaAttack::~Boss1LavaAttack()
{
	delete hitBox;
	bossPointer->getBossScene()->removeChild(sprite);
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
	: Boss1LavaAttack(bossInstance, "Sprites/spit_sprite.png")
{
	auto anim = cocos2d::AnimationCache::getInstance()->getAnimation("boss_spit_animation_key");
	auto action = cocos2d::Animate::create(anim);
	sprite->stopAllActions();
	sprite->runAction(cocos2d::Repeat::create(action->clone(), 1));

	switch (order)
	{
	case 1:
		waitingTime = 1.5;
		position = cocos2d::Vec2(250, 500);
		break;
	case 2:
		waitingTime = 2;
		position = cocos2d::Vec2(250, 200);
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


	//Set physic variables
	acceleration.set(2000, 0);
	velocity.set(1000, 0);

	//Set sprite size
	hitBox = new HitBox(bossPointer->getBossScene(), 50.f, 50);
}

LavaBall::~LavaBall()
{
	bossPointer->removeFromLavaList(this);
}

void LavaBall::update(const float& deltaT)
{
	if (waitingTime > 0)
	{
		waitingTime -= deltaT;
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

FlameThrower::FlameThrower(Boss *bossInstance)
	: Boss1LavaAttack(bossInstance, "Sprites/flame_sprite.png"), onTime(1.0f), drawNode(cocos2d::DrawNode::create())
{
	position.set(960, 500);

	//Play animation
	sprite->stopAllActions();
	auto action = cocos2d::Animate::create(cocos2d::AnimationCache::getInstance()->getAnimation("boss_flame_animation_key"));
	sprite->runAction(cocos2d::Repeat::create(action->clone(), 1));

	//
	sprite->setPosition(position);

	//Setup hit box
	hitBox = new HitBox(bossPointer->getBossScene(), 450, 1920);
}

FlameThrower::~FlameThrower()
{
	bossPointer->removeFromLavaList(this);
}

void FlameThrower::update(const float& deltaT)
{
	onTime -= deltaT;
	hitBox->updateHitBox(position);
	if (onTime <= 0)
	{
		delete this;
	}
}


/********************************************************************************************************
 *
 *
 *										Explosive Bullet Functions
 *
 *
 *******************************************************************************************************/


ExplosionArea::ExplosionArea(cocos2d::Vec2& startPos, Boss *bossInstance)
	: Boss1LavaAttack(bossInstance,"Sprites/ExplosiveArea.png"), onTime(3)
{
	position.set(startPos);
	sprite->setPosition(position);

	//
	hitBox = new HitBox(bossPointer->getBossScene(), 100, 100);

	bossPointer->getLavaList().push_back(this);
}

ExplosionArea::~ExplosionArea()
{
	bossPointer->removeFromLavaList(this);
}

void ExplosionArea::update(const float& deltaT)
{
	onTime -= deltaT;
	if (onTime <= 0)
		delete this;
}


ExplosiveBullet::ExplosiveBullet(const cocos2d::Vec2& heroLocation, Boss* bossInstance)
	: Boss1LavaAttack(bossInstance, "Sprites/spit_sprite.png")
{
	//Set up the sprite
	position.set(bossInstance->getMouthPosition());
	sprite->setPosition(position);

	//Set up hit box
	hitBox = new HitBox(bossPointer->getBossScene(), 50.f, 50);


	//set up the physics
	cocos2d::Vec2 tempVector = heroLocation - bossInstance->getMouthPosition();
	lengthVector = tempVector.getLength();
	acceleration = tempVector.getNormalized() * 500;

	this->heroLocation = heroLocation;
}

ExplosiveBullet::~ExplosiveBullet()
{
	bossPointer->removeFromLavaList(this);
	auto tempExplosiveArea = new ExplosionArea(position, bossPointer);
}

/*
 * @brief This function updates the position of the bullet
 */
void ExplosiveBullet::update(const float& deltaT)
{
	//physics update
	lastPosition = position;
	velocity += acceleration * deltaT;
	position += velocity * deltaT;
	traveledLength += (lastPosition - position).getLength();

	//Update the sprite
	sprite->setPosition(position);
	hitBox->updateHitBox(position);

	//Delete the object if the position reaches the target location
	if (lengthVector <= traveledLength)
	{
		delete this;
	}
}
