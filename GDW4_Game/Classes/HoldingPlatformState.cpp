#include "HoldingPlatformState.h"
#include "Hero.h"
#include "HeroStateManager.h"
#include "Grapple.h"

HoldingPlatformState::HoldingPlatformState()
{
}


HoldingPlatformState::~HoldingPlatformState()
{
}

void HoldingPlatformState::onEnter()
{
	HeroStateManager::currentState = this;

	Hero::hero->sprite->stopAllActions();
}

void HoldingPlatformState::onExit()
{
	HeroStateManager::falling->onEnter();
}

void HoldingPlatformState::handleInput(InputType input)
{
	switch (input)
	{
	case InputType::p_s: //let go of the platform and start falling down
		Grapple::grapple->unLatch();
		HeroStateManager::falling->onEnter();
		break;

	case InputType::p_space: //jump from the holding position
		HeroStateManager::grappleJumping->onEnter();
		break;
	}
}

void HoldingPlatformState::update(float dt)
{
	Hero::hero->velocity.y = 0;
	if (!Grapple::grapple->isActive)
		onExit();
}