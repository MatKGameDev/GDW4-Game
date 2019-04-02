#include "Boss/Ability States/DeathState.h"

DeathState::DeathState(Boss* bossInstance)
	: FirstBossState(bossInstance)
{
	//Get animation

	//Run action
}

/**
 * @brief Changes to victory scene when the boss finish
 * doing death animation
 */
void DeathState::changeToVictoryScreen()
{
}
