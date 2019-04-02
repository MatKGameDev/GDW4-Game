#pragma once
#ifndef GRAPPLINGSTATE_H
#define GRAPPLINGSTATE_H

#include "HeroStateBase.h"
class GrapplingState : public HeroStateBase
{
public:
	GrapplingState();
	~GrapplingState();

	void onEnter();
	void onExit();
	void handleInput(InputType input);

	void update(float dt);
};
#endif