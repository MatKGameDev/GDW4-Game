#include "Boss/Attacks/FlameThrowerProjectile.h"
#include "Boss/General/Boss.h"

FlameThrower::FlameThrower(Boss *bossInstance)
	: Boss1LavaAttack(bossInstance, "Sprites/flame_sprite.png"), onTime(1.0f), drawNode(cocos2d::DrawNode::create())
{
	position.set(1000, 350);

	//Play animation
	sprite->stopAllActions();
	auto action = cocos2d::Animate::create(cocos2d::AnimationCache::getInstance()->getAnimation("boss_flame_animation_key"));
	sprite->runAction(cocos2d::Repeat::create(action->clone(), 1));

	//
	sprite->setPosition(position);
	bossPointer->getBossScene()->removeChild(sprite, false);
	bossPointer->getBossScene()->addChild(sprite, 16);

	//Setup hit box
	hitBox = new HitBox(bossPointer->getBossScene(), 200, 1920);


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