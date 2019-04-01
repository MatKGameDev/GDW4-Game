#include "Boss/Ability States/RestingState.h"

RestingState::RestingState(Boss* aBossInstance)
	:FirstBossState(aBossInstance), onTime(3.f)
{
	//Get animation

	//Run action
}

/**
 * @brief Reduce the onTime for the state
 * @param deltaTime The change of time from last frame to current frame
 */
void RestingState::update(const float& deltaTime)
{
	onTime -= deltaTime;
	if (onTime <= 0)
		changeToIdleState();
}
