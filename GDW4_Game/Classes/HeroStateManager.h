#pragma once
#include "AttackingState.h"
#include "FallingState.h"
#include "GrapplingState.h"
#include "IdleState.h"
#include "JumpingState.h"
#include "RunningState.h"
#include "GrappleJumpState.h"
#include "HoldingPlatformState.h"

class HeroStateManager
{
public:
	HeroStateManager();
	~HeroStateManager();

	static HeroStateBase* currentState;
	static AttackingState* attacking;
	static FallingState* falling;
	static GrapplingState* grappling;
	static IdleState* idle;
	static JumpingState* jumping;
	static RunningState* running;
	static GrappleJumpState* grappleJumping;
	static HoldingPlatformState* holdingPlatform;
};