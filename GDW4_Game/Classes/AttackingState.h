#pragma once
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