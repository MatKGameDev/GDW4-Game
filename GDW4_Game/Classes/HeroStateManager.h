#pragma once
#ifndef HEROSTATEMANAGER_H
#define HEROSTATEMANAGER_H

#include "AttackingState.h"
#include "DyingState.h"
#include "FallingState.h"
#include "GrapplingState.h"
#include "IdleState.h"
#include "JumpingState.h"
#include "RunningState.h"
#include "GrappleJumpState.h"
#include "HoldingPlatformState.h"
#include "ShootingGrappleState.h"

class HeroStateManager
{
public:
	HeroStateManager();
	~HeroStateManager();

	static HeroStateBase* currentState;
	static AttackingState* attacking;
	static DyingState* dying;
	static FallingState* falling;
	static GrapplingState* grappling;
	static IdleState* idle;
	static JumpingState* jumping;
	static RunningState* running;
	static GrappleJumpState* grappleJumping;
	static HoldingPlatformState* holdingPlatform;
	static ShootingGrappleState* shootingGrapple;
};
#endif