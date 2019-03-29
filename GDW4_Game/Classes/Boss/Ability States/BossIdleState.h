#pragma once
#include "FirstBossState.h"

class Idling4FirstBoss : public FirstBossState
{
public:
	Idling4FirstBoss(Boss *boss);
	void update(const float &deltaT) override;


private:
	float cooldownBeforeNextAbility;

	//Utility functions
	/*
	 * List	of utility functions
	 * 1. Choose a random ability
	 */
	void chooseRandomAbility();
};