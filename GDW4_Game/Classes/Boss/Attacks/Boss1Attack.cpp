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

/**
 * @brief This class update its data members
 */
void Boss1LavaAttack::update(const float& deltaT)
{
	hitBox->updateHitBox(position);
}

/**
 * @brief This function will resolve the attack object
 * when it collides with hero
 */
void Boss1LavaAttack::hitByHero()
{
}

/**
 * @brief This function will resolve the attack object
 * when it collides with an environment object
 */
void Boss1LavaAttack::hitByEnvironment()
{
}

/**
 * @brief Gets the hitbox for the attack
 * 
 * @return Return cocos2d::Rect
 */
cocos2d::Rect Boss1LavaAttack::getHitBox() const
{
	return hitBox->hitBox;
}

Boss1LavaAttack::BossAttack Boss1LavaAttack::getAttackType() const
{
	return attackType;
}
