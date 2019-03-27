#pragma once
#include "FirstBossState.h"

class FlameSplit4FirstBoss : public FirstBossState
{
	void performAction();
	void changeBackToIdling();
	Boss *something;
public:
	FlameSplit4FirstBoss(Boss *boss);
};