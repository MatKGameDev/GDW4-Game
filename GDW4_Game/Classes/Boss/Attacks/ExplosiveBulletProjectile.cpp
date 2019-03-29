#include "Boss/Attacks/ExplosiveBulletProjectile.h"
#include "Boss/General/Boss.h"


ExplosiveBullet::ExplosiveBullet(const cocos2d::Vec2& heroLocation, Boss* bossInstance)
	: Boss1LavaAttack(bossInstance, "Sprites/spit_sprite.png")
{
	//Set up the sprite
	position.set(300,300);
	sprite->setPosition(position);

	//Set up the animation
	const auto animation = cocos2d::Animate::create
	(
		cocos2d::AnimationCache::getInstance()->getAnimation("boss_explosive_PRE_animation_key")
	);

	sprite->stopAllActions();
	sprite->runAction
	(
		cocos2d::Sequence::create
		(
			cocos2d::Repeat::create(animation->clone(), 1),
			cocos2d::CallFunc::create([&] {isWaiting = false; }),
			nullptr
		)
	);

	//Set up hit box
	hitBox = new HitBox(bossPointer->getBossScene(), 50.f, 50);

	//set up the physics
	cocos2d::Vec2 tempVector = heroLocation - position;
	float lengthVector = tempVector.getLength();
	acceleration = tempVector.getNormalized() * 2000;
	velocity = tempVector.getNormalized() * 1250;
}

ExplosiveBullet::~ExplosiveBullet()
{
	bossPointer->removeFromLavaList(this);
}

void ExplosiveBullet::update(const float& deltaT)
{
	if (!isWaiting)
	{
		//physics update
		velocity += acceleration * deltaT;
		position += velocity * deltaT;

		//Update the sprite
		sprite->setPosition(position);
		hitBox->updateHitBox(position);
	}
}