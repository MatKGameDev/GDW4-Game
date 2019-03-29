#include "Boss/Attacks/ExplosiveBulletProjectile.h"
#include "Boss/General/Boss.h"


ExplosiveArea::ExplosiveArea(const cocos2d::Vec2& startPosition, Boss* bossInstance)
	: Boss1LavaAttack(bossInstance, "Sprites/spit_sprite.png")
{
	//Set up the sprite
	position = startPosition;
	sprite->setPosition(position);

	hitBox = new HitBox(bossPointer->getBossScene(), 120, 120);

	//Set up the animation
	const auto animation = cocos2d::Animate::create
	(
		cocos2d::AnimationCache::getInstance()->getAnimation("boss_explosive_POST_animation_key")
	);

	sprite->runAction
	(
		cocos2d::Sequence::create
		(
			cocos2d::Repeat::create(animation, 1),
			cocos2d::CallFunc::create([&] {delete this; }),
			nullptr
		)
	);

}

ExplosiveArea::~ExplosiveArea()
{
	bossPointer->removeFromLavaList(this);
}

void ExplosiveArea::update(const float& deltaT)
{
	hitBox->updateHitBox(position);
}

ExplosiveBullet::ExplosiveBullet(const cocos2d::Vec2& heroLocation, Boss* bossInstance)
	: Boss1LavaAttack(bossInstance, "Sprites/spit_sprite.png")
{
	//Set up the sprite
	position.set(300, 300);
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
			cocos2d::CallFunc::create([&] {setUpPhysic(heroLocation); isWaiting = false; }),
			nullptr
		)
	);

	//Set up hit box
	hitBox = new HitBox(bossPointer->getBossScene(), 50, 50);

}

ExplosiveBullet::~ExplosiveBullet()
{
	bossPointer->removeFromLavaList(this);
	bossPointer->addAttack(new ExplosiveArea(position, bossPointer));
}

void ExplosiveBullet::update(const float& deltaT)
{
	if (!isWaiting)
	{
		//physics update
		velocity += acceleration * deltaT;
		position += velocity * deltaT;
		
		////Update the sprite
		sprite->setPosition(position);
		hitBox->updateHitBox(position);
	}
}

void ExplosiveBullet::hitByHero()
{
	delete this;
}

void ExplosiveBullet::setUpPhysic(const cocos2d::Vec2& heroPos)
{
	cocos2d::Vec2 tempVector = heroPos - position;
	float lengthVector = tempVector.getLength();
	acceleration = tempVector.getNormalized() * 2000;
	velocity = tempVector.getNormalized() * 1250;
}
