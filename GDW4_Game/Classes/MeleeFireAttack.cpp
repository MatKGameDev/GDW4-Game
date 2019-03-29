#include "MeleeFireAttack.h"
#include "Hero.h"
#include "EmptyAttack.h"
#include "HeroAttackManager.h"

MeleeFireAttack::MeleeFireAttack()
{
	attackTimer = 0.0f;
	attackWindup = 0.2f;
	attackDuration = 0.2f;
	attackCooldown = 0.12f;
	disabled = false;
}

//directional attacks (set attack hitbox based on direction)
void MeleeFireAttack::attackUp()
{
	hitbox.setRect(
		Hero::hero->hurtBox.getMinX() - 20,
		Hero::hero->getBottomPos() + Hero::hero->height / 1.5,
		Hero::hero->hurtBox.size.width + 40,
		120);
}
void MeleeFireAttack::attackDown()
{
	hitbox.setRect(
		Hero::hero->hurtBox.getMinX() - 20,
		Hero::hero->getBottomPos() + Hero::hero->height / 2.5,
		Hero::hero->hurtBox.size.width + 40,
		-120);
}
void MeleeFireAttack::attackLeft()
{
	hitbox.setRect(
		Hero::hero->hurtBox.getMaxX() - 120,
		Hero::hero->getBottomPos() + Hero::hero->height / 2.5,
		120,
		50);
}
void MeleeFireAttack::attackRight()
{
	hitbox.setRect(
		Hero::hero->hurtBox.getMinX(),
		Hero::hero->getBottomPos() + Hero::hero->height / 2.5,
		120,
		50);
}

//initialize the attack
void MeleeFireAttack::initAttack()
{
	//aim upwards
	if (HeroAttackBase::isWKeyHeld)
	{
		performAttack = &MeleeFireAttack::attackUp; //setting member function pointer

		if (Hero::hero->lookState == Hero::LookDirection::lookingRight)
		{
			auto anim = cocos2d::AnimationCache::getInstance()->getAnimation("melee_up_right_animation_key");
			auto action = cocos2d::Animate::create(anim);
			Hero::hero->sprite->stopAllActions();
			Hero::hero->sprite->runAction(cocos2d::CCRepeat::create(action->clone(), 1));
		}
		else
		{
			auto anim = cocos2d::AnimationCache::getInstance()->getAnimation("melee_up_left_animation_key");
			auto action = cocos2d::Animate::create(anim);
			Hero::hero->sprite->stopAllActions();
			Hero::hero->sprite->runAction(cocos2d::CCRepeat::create(action->clone(), 1));
		}
	}

	//aim downwards
	else if (HeroAttackBase::isSKeyHeld)
		performAttack = &MeleeFireAttack::attackDown;

	//aim right
	else if (Hero::hero->lookState == Hero::LookDirection::lookingRight)
	{
		performAttack = &MeleeFireAttack::attackRight;

		auto anim = cocos2d::AnimationCache::getInstance()->getAnimation("melee_right_animation_key");
		auto action = cocos2d::Animate::create(anim);
		Hero::hero->sprite->stopAllActions();
		Hero::hero->sprite->runAction(cocos2d::CCRepeat::create(action->clone(), 1));
	}

	//aim left
	else if (Hero::hero->Hero::hero->lookState == Hero::LookDirection::lookingLeft)
	{
		
		performAttack = &MeleeFireAttack::attackLeft;

		auto anim = cocos2d::AnimationCache::getInstance()->getAnimation("melee_left_animation_key");
		auto action = cocos2d::Animate::create(anim);
		Hero::hero->sprite->stopAllActions();
		Hero::hero->sprite->runAction(cocos2d::CCRepeat::create(action->clone(), 1));
	}
}

void MeleeFireAttack::update(float dt)
{
	//before the attack hitbox should appear
	if (attackTimer < attackWindup)
	{
		attackTimer += dt;
	}
	//during the attack duration
	else if (attackTimer < attackDuration + attackWindup)
	{
		if (disabled)
			hitbox = hitbox.ZERO; //deactivate hitbox
		else //attack is not disabled
			(this->*performAttack)(); //calling member function pointer

		attackTimer += dt;
	}
	//after the attack is finished
	else
	{
		attackTimer = 0.0f;
		hitbox = hitbox.ZERO; //deactivate hitbox
		disabled = false; //undisable if needed
		HeroAttackManager::empty->attackCooldown = this->attackCooldown;
		HeroAttackManager::setCurrentAttack(HeroAttackTypes::emptyA, nullptr);
	}
}