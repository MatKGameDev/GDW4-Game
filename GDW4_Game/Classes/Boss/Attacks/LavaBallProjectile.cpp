#include "Boss/Attacks/LavaBallProjectile.h"
#include "Boss/General/Boss.h"

LavaBall::LavaBall(int order, Boss *bossInstance)
	: Boss1LavaAttack(bossInstance, "Sprites/spit_sprite.png")
{

	//Set Position for the lava ball
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
	sprite->setPosition(position);

	//Set physic variables
	acceleration.set(2000, 0);
	velocity.set(1000, 0);

	//Set sprite size
	hitBox = new HitBox(bossPointer->getBossScene(), 50.f, 50);

	//Set up animation for sprite
	const auto animation = cocos2d::Animate::create
	(
		cocos2d::AnimationCache::getInstance()->getAnimation("boss_spit_animation_key")
	);

	sprite->stopAllActions();
	sprite->runAction(cocos2d::Repeat::create(animation->clone(), 1));
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
		sprite->setPosition(position);
		hitBox->updateHitBox(position);

		//Delete the object when it goes out of the screen
		if (position.x > 1920)
			delete this;
	}
}