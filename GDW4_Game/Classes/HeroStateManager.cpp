#include "HeroStateManager.h"

AttackingState* HeroStateManager::attacking = new AttackingState();
FallingState* HeroStateManager::falling = new FallingState();
GrapplingState* HeroStateManager::grappling = new GrapplingState();
IdleState* HeroStateManager::idle = new IdleState();
JumpingState* HeroStateManager::jumping = new JumpingState();
RunningState* HeroStateManager::running = new RunningState();
GrappleJumpState* HeroStateManager::grappleJumping = new GrappleJumpState();
HoldingPlatformState* HeroStateManager::holdingPlatform = new HoldingPlatformState();

HeroStateBase* HeroStateManager::currentState = idle; //initialize to idle state


HeroStateManager::HeroStateManager()
{
}


HeroStateManager::~HeroStateManager()
{
}