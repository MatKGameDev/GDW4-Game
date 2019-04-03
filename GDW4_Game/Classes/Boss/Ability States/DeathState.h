#pragma once
#include "Boss/Ability States/FirstBossState.h"

class DeathState: public FirstBossState
{
public:
	DeathState(Boss *bossInstance);
private:
	void changeToVictoryScreen();
	void removeAllElements();
};
