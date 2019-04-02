#include "Boss1Attack.h"
#include "Boss/General/Boss.h"
#include "Boss/General/HitBox.h"

Boss1LavaAttack::Boss1LavaAttack(Boss* bossInstance, const std::string& fileName)
	: bossPointer(bossInstance), sprite(cocos2d::Sprite::create(fileName))
{
	bossPointer->getBossScene()->addChild(sprite, 18);
}

Boss1LavaAttack::~Boss1LavaAttack()
{
	delete hitBox;
	bossPointer->getBossScene()->removeChild(sprite);
}


void Boss1LavaAttack::hitByHero()
{
}

void Boss1LavaAttack::hitByEnvironment()
{
}

cocos2d::Rect Boss1LavaAttack::getHitBox() const
{
	return hitBox->hitBox;
}

Boss1LavaAttack::BossAttack Boss1LavaAttack::getAttackType() const
{
	return attackType;
}
