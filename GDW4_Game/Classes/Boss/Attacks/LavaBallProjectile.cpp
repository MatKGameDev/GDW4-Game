#include "Boss/Attacks/LavaBallProjectile.h"
#include "Boss/General/Boss.h"
#include "Hero.h"

LavaBall::LavaBall(int order, Boss *bossInstance)
	: Boss1LavaAttack(bossInstance, "Sprites/spit_sprite.png")
{
	attackType = BossAttack::LavaBall;

	//Set Position for the lava ball
	switch (order)
	{
	case 1:
		waitingTime = 0.5;
		position = cocos2d::Vec2(350, 450);
		break;
	case 2:
		waitingTime = 1.1;
		position = cocos2d::Vec2(350, 600); 
		break;
	case 3:
		waitingTime = 1.6;
		position = cocos2d::Vec2(350, 300); 
		break;
	case 4:
		waitingTime = 2.2;
		position = cocos2d::Vec2(350, 750); 
		break;
	case 5:
		waitingTime = 2.8;
		position = cocos2d::Vec2(350, 150); 
		break;
	default:
		throw;
	}
	
	//Set physic variables
	sprite->setPosition(position);

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
			cocos2d::CallFunc::create([&]{setUpPhysics();isWaiting = false;}),
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
		//setUpPhysics();
		velocity += acceleration * deltaT;
		position += velocity * deltaT;
		sprite->setPosition(position);
		hitBox->updateHitBox(position);
	}
}

void LavaBall::hitByEnvironment()
{
	delete this;
}

void LavaBall::hitByHero()
{
	delete this;
}


void LavaBall::setUpPhysics()
{
	const cocos2d::Vec2 tempVector = Hero::hero->sprite->getPosition() - position;
	acceleration = tempVector.getNormalized() * 2000;
	velocity = tempVector.getNormalized() * 750;
}
