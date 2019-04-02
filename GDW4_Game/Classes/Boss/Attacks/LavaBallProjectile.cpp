#include "Boss/Attacks/LavaBallProjectile.h"
#include "Boss/General/Boss.h"

LavaBall::LavaBall(int order, Boss *bossInstance)
	: Boss1LavaAttack(bossInstance, "Sprites/spit_sprite.png")
{
	attackType = BossAttack::LavaBall;

	//Set Position for the lava ball
	switch (order)
	{
	case 1:
		waitingTime = 0.5;
		position = cocos2d::Vec2(350, 500);
		break;
	case 2:
		waitingTime = 1;
		position = cocos2d::Vec2(350, 200);
		break;
	case 3:
		waitingTime = 1.5;
		position = cocos2d::Vec2(350, 750);
		break;
	default:
		throw;
	}
	
	//Set physic variables
	sprite->setPosition(position);
	acceleration.set(2000, 0);
	velocity.set(1000, 0);

	//Set sprite size
	hitBox = new HitBox(position, 50.f, 50);

	//Set up animation for sprite
	const auto animation = marcos::AnimationManager::getAnimation("boss_spit_animation_key");

	//Run the actions
	sprite->runAction
	(
		cocos2d::Sequence::create
		(
			cocos2d::Repeat::create(animation->clone(), 1),
			cocos2d::DelayTime::create(waitingTime),
			cocos2d::CallFunc::create([&] {isWaiting = false; }),
			nullptr
		)
	);
}

LavaBall::~LavaBall()
{
	bossPointer->removeFromLavaList(this);
}

void LavaBall::update(const float& deltaT)
{
	if (!isWaiting)
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

void LavaBall::hitByEnvironment()
{
	delete this;
}
