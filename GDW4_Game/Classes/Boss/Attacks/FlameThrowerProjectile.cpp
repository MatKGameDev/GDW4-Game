#include "Boss/Attacks/FlameThrowerProjectile.h"
#include "Boss/General/Boss.h"

FlameThrower::FlameThrower(Boss *bossInstance)
	: Boss1LavaAttack(bossInstance, "Sprites/flame_sprite.png")
{
	//Set sprite
	position.set(1000, 350);
	sprite->setPosition(position);
	bossPointer->getBossScene()->removeChild(sprite, false);
	bossPointer->getBossScene()->addChild(sprite, 16);
	attackType = BossAttack::Flamethrower;

	//Get all animations
	const auto startingAnimation = marcos::AnimationManager::getAnimationWithAnimationTime("boss_flame_PRE_animation_key",1.5);
	const auto midAnimation = marcos::AnimationManager::getAnimationWithAnimationTime("boss_flame_MID_animation_key",1.5);
	const auto finishingAnimation = marcos::AnimationManager::getAnimation("boss_flame_POST_animation_key");

	//Run actions
	sprite->runAction
	(
		cocos2d::Sequence::create
		(
			cocos2d::Repeat::create(startingAnimation, 1),
			cocos2d::CallFunc::create([&] {hitBox->setNewSize(1920, 230); }),
			cocos2d::Repeat::create(midAnimation, 1),
			cocos2d::CallFunc::create([&] {hitBox->setNewSize(0, 0); }),
			cocos2d::Repeat::create(finishingAnimation,1),
			cocos2d::CallFunc::create([&] {delete this; }),
			nullptr
		)
	);

	//Set hit box
	hitBox = new HitBox(position, 0, 0);

	dealingDamage = 2;
}

FlameThrower::~FlameThrower()
{
	bossPointer->removeFromLavaList(this);
}