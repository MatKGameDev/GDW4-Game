#include "MeleeFireAttack.h"
#include "Hero.h"
#include "EmptyAttack.h"
#include "HeroAttackManager.h"

MeleeFireAttack::MeleeFireAttack()
{
	attackTimer = 0.0f;
	attackDuration = 0.3f;
	attackCooldown = 0.7f;
}

void MeleeFireAttack::update(float dt)
{
	if (attackTimer < attackDuration)
	{
		//aim upwards
		if (HeroAttackBase::isWKeyHeld)
		{
			hitbox.setRect(
				Hero::hero->hurtBox.getMinX() - 20,
				Hero::hero->getBottomPos() + Hero::hero->height / 1.5,
				Hero::hero->hurtBox.size.width + 40,
				120);
		}
		//aim upwards
		else if (HeroAttackBase::isSKeyHeld)
		{
			hitbox.setRect(
				Hero::hero->hurtBox.getMinX() - 20,
				Hero::hero->getBottomPos() + Hero::hero->height / 2.5,
				Hero::hero->hurtBox.size.width + 40,
				-120);
		}
		//aim right
		else if (Hero::hero->isMovingRight) //TODO: change to looking right after merging
		{
			hitbox.setRect(
				Hero::hero->hurtBox.getMinX(),
				Hero::hero->getBottomPos() + Hero::hero->height / 2.5,
				110,
				50);
		}
		//aim left
		else if (Hero::hero->isMovingLeft) //TODO: change to looking left after merging
		{
			hitbox.setRect(
				Hero::hero->hurtBox.getMaxX(),
				Hero::hero->getBottomPos() + Hero::hero->height / 2.5,
				-110,
				50);
		}

		attackTimer += dt;
	}
	else if (attackTimer < attackDuration + attackCooldown)
	{
		attackTimer += dt;
		hitbox = hitbox.ZERO; //deactivate hitbox
	}
	else
	{
		HeroAttackManager::setCurrentAttack(HeroAttackTypes::emptyA);
		attackTimer = 0.0f;
	}
}