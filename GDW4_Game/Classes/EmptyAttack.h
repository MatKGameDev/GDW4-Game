#pragma once
#include "HeroAttack.h"

class EmptyAttack : public HeroAttack
{
public:
	EmptyAttack();

	void update(float dt);
};