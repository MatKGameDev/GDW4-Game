#include "Boss/Attacks/FlameThrowerProjectile.h"
#include "Boss/General/Boss.h"

FlameThrower::FlameThrower(Boss *bossInstance)
	: Boss1LavaAttack(bossInstance, "Sprites/flame_sprite.png"), onTime(1.0f), drawNode(cocos2d::DrawNode::create())
{
	position.set(1000, 350);

	//Play animation
	sprite->stopAllActions();
	const auto startingAnimation = cocos2d::Animate::create
	(
		cocos2d::AnimationCache::getInstance()->getAnimation("boss_flame_PRE_animation_key")
	);

	const auto midAnimation = cocos2d::Animate::create
	(
		cocos2d::AnimationCache::getInstance()->getAnimation("boss_flame_MID_animation_key")
	);

	const auto finishingAnimation = cocos2d::Animate::create
	(
		cocos2d::AnimationCache::getInstance()->getAnimation("boss_flame_POST_animation_key")
	);

	sprite->stopAllActions();
	sprite->runAction
	(
		cocos2d::Sequence::create
		(
			cocos2d::Repeat::create(startingAnimation, 1),
			cocos2d::CallFunc::create([&] {hitBox->setNewSize(1920, 200); }),
			cocos2d::Repeat::create(midAnimation, 1),
			cocos2d::CallFunc::create([&] {hitBox->setNewSize(0, 0); }),
			cocos2d::Repeat::create(finishingAnimation,1),
			cocos2d::CallFunc::create([&] {delete this; }),
			nullptr
		)

	);

	hitBox = new HitBox(position, 0, 0, bossPointer->getBossScene());

	//
	sprite->setPosition(position);
	bossPointer->getBossScene()->removeChild(sprite, false);
	bossPointer->getBossScene()->addChild(sprite, 16);


}

FlameThrower::~FlameThrower()
{
	bossPointer->removeFromLavaList(this);
}

void FlameThrower::update(const float& deltaT)
{
		hitBox->updateHitBox(position);
}