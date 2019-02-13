#pragma once
#include "HeroMovementBase.h"

class HeroMoveLeft : public HeroMovementBase
{
public:
	HeroMoveLeft();

	void init();
	void update(float dt);
};