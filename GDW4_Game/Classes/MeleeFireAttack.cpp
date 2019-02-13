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
		Hero::hero->hurtBox.getMaxX(),
		Hero::hero->getBottomPos() + Hero::hero->height / 2.5,
		-110,
		50);
}
void MeleeFireAttack::attackRight()
{
	hitbox.setRect(
		Hero::hero->hurtBox.getMinX(),
		Hero::hero->getBottomPos() + Hero::hero->height / 2.5,
		110,
		50);
}

//initialize the attack
void MeleeFireAttack::initAttack()
{
	//aim upwards
	if (HeroAttackBase::isWKeyHeld)
		performAttack = &MeleeFireAttack::attackUp; //setting member function pointer

	//aim downwards
	else if (HeroAttackBase::isSKeyHeld)
		performAttack = &MeleeFireAttack::attackDown;

	//aim right
	else if (Hero::hero->lookState == Hero::LookDirection::lookingRight)
		performAttack = &MeleeFireAttack::attackRight;

	//aim left
	else if (Hero::hero->Hero::hero->lookState == Hero::LookDirection::lookingLeft)
		performAttack = &MeleeFireAttack::attackLeft;
}

void MeleeFireAttack::update(float dt)
{
	//during the attack duration
	if (attackTimer < attackDuration)
	{
		(this->*performAttack)(); //calling member function pointer

		attackTimer += dt;
	}
	//during the attack cooldown
	else if (attackTimer < attackDuration + attackCooldown)
	{
		attackTimer += dt;
		hitbox = hitbox.ZERO; //deactivate hitbox
	}
	//after the attack cooldown is finished
	else
	{
		attackTimer = 0.0f;
		HeroAttackManager::setCurrentAttack(HeroAttackTypes::emptyA, nullptr);
	}
}