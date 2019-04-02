#pragma once
#include "FirstBossState.h"


class Idling4FirstBoss : public FirstBossState
{
public:
	//Constructor
	Idling4FirstBoss(Boss *boss);
	~Idling4FirstBoss();

	//Member functions
	void update(const float &deltaT) override;
private:
	float cooldownBeforeNextAbility;
	static int numberOfCast;
	static const int maxNumberOfCastPerRound;

	//Utility functions
	void chooseRandomAbility();
};