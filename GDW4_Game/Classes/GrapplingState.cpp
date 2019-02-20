#include "GrapplingState.h"
#include "Grapple.h"
#include "HeroStateManager.h"
#include "Hero.h"


GrapplingState::GrapplingState()
{
}


GrapplingState::~GrapplingState()
{
}

void GrapplingState::onEnter()
{
	HeroStateManager::currentState = this;

	Hero::hero->sprite->stopAllActions();
}

void GrapplingState::onExit()
{
	if (Grapple::grapple->isHeroAtEndPoint)
		HeroStateManager::holdingPlatform->onEnter();
	else if (!Grapple::grapple->isActive)
		HeroStateManager::falling->onEnter();
}

void GrapplingState::handleInput(InputType input)
{
}

void GrapplingState::update(float dt)
{
	if (Grapple::grapple->isHeroAtEndPoint || !Grapple::grapple->isActive)
		onExit();
}
