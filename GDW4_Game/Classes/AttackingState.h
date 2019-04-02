#pragma once
#ifndef ATTACKINGSTATE_H
#define ATTACKINGSTATE_H

#include "HeroStateBase.h"
class AttackingState : public HeroStateBase
{
public:
	AttackingState();
	~AttackingState();

	void onEnter();
	void onExit();
	void handleInput(InputType input);

	void update(float dt);
};
#endif