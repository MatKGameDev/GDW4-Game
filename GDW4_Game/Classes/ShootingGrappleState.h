#pragma once
#include "HeroStateBase.h"

class ShootingGrappleState : public HeroStateBase
{
public:
	ShootingGrappleState();
	~ShootingGrappleState();

	void onEnter();
	void onExit();
	void handleInput(InputType input);
	void update(float dt);
};