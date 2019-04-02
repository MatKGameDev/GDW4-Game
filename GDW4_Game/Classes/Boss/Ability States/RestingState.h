#pragma once
#include "Boss/Ability States/FirstBossState.h"

/**
 *
 */
class RestingState: public FirstBossState
{
	float onTime{0};
public:
	RestingState(Boss* aBossInstance);
	void update(const float& deltaTime) override;
};