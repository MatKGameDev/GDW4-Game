#include "ProjectileIceAttack.h"
#include "HeroAttackManager.h"
#include "IceProjectile.h"
#include "Hero.h"

ProjectileIceAttack::ProjectileIceAttack()
{
	attackTimer = 0.0f;
	attackCooldown = 0.7f;
}

void ProjectileIceAttack::initAttack()
{
	//aim upwards
	if (HeroAttackBase::isWKeyHeld)
		IceProjectile* newProjectile = new IceProjectile(Vect2(0, IceProjectile::SPEED));

	//aim downwards
	else if (HeroAttackBase::isSKeyHeld)
		IceProjectile* newProjectile = new IceProjectile(Vect2(0, -IceProjectile::SPEED));

	//aim right
	else if (Hero::hero->lookState == Hero::LookDirection::lookingRight)
		IceProjectile* newProjectile = new IceProjectile(Vect2(IceProjectile::SPEED, 0));

	//aim left
	else if (Hero::hero->Hero::hero->lookState == Hero::LookDirection::lookingLeft)
		IceProjectile* newProjectile = new IceProjectile(Vect2(-IceProjectile::SPEED, 0));
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
		HeroAttackManager::setCurrentAttack(HeroAttackTypes::emptyA);
	}
}
