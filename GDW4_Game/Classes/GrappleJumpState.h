#pragma once
#ifndef GRAPPLEJUMPSTATE_H
#define GRAPPLEJUMPSTATE_H

#include "HeroStateBase.h"

class GrappleJumpState : public HeroStateBase
{
public:
	GrappleJumpState();
	~GrappleJumpState();

	void onEnter();
	void onExit();
	void handleInput(InputType input);

	void update(float dt);
};
#endif