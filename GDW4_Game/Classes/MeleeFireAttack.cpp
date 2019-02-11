#include "MeleeFireAttack.h"
#include "Hero.h"
//#include "HeroAttackState.h"

MeleeFireAttack::MeleeFireAttack()
{
	attackTimer = 0.0f;
	attackDuration = 0.3f;
	attackCooldown = 0.5f;
}

void MeleeFireAttack::update(float dt)
{
	if (attackTimer < attackDuration)
	{
		hitbox.setRect(Hero::hero->hurtBox.getMaxX(),
			Hero::hero->getBottomPos() + Hero::hero->height / 4,
			50, 90);
		
		attackTimer += dt;
	}
	else if (attackTimer < attackDuration + attackCooldown)
	{
		attackTimer += dt;
		hitbox = hitbox.ZERO; //deactivate hitbox
	}
	else
	{
		//Hero::hero->currentAttack = HeroAttackState::empty;
		attackTimer = 0.0f;
	}
}