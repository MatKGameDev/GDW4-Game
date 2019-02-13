#include "ProjectileIceAttack.h"
#include "HeroAttackManager.h"
#include "IceProjectile.h"
#include "Hero.h"

ProjectileIceAttack::ProjectileIceAttack()
{
	attackTimer = 0.0f;
	attackCooldown = 0.9f;
}

void ProjectileIceAttack::initAttack(cocos2d::Scene* scene)
{
	IceProjectile* newProjectile = new IceProjectile();

	//aim upwards
	if (HeroAttackBase::isWKeyHeld)
		newProjectile->velocity = Vect2(0, IceProjectile::SPEED);

	//aim downwards
	else if (HeroAttackBase::isSKeyHeld)
		newProjectile->velocity = Vect2(0, -IceProjectile::SPEED);

	//aim right
	else if (Hero::hero->lookState == Hero::LookDirection::lookingRight)
		newProjectile->velocity = Vect2(IceProjectile::SPEED, 0);

	//aim left
	else //(Hero::hero->Hero::hero->lookState == Hero::LookDirection::lookingLeft)
		newProjectile->velocity = Vect2(-IceProjectile::SPEED, 0);

	scene->addChild(newProjectile->sprite, 15);
}

void ProjectileIceAttack::update(float dt)
{
	//during the attack cooldown
	if (attackTimer < attackCooldown)
	{
		attackTimer += dt;
		hitbox = hitbox.ZERO; //deactivate hitbox
	}
	else
	{
		attackTimer = 0.0f;
		HeroAttackManager::setCurrentAttack(HeroAttackTypes::emptyA, nullptr);
	}
}
