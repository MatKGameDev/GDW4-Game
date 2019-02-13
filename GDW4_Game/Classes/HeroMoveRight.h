#pragma once
#include "HeroMovementBase.h"

class HeroMoveRight : public HeroMovementBase
{
public:
	HeroMoveRight();

	void init();
	void update(float dt);
};