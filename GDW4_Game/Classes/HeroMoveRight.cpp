#include "HeroMoveRight.h"
#include "Hero.h"

HeroMoveRight::HeroMoveRight()
{
}

void HeroMoveRight::init()
{
	//do initial animation stuff here
}

void HeroMoveRight::update(float dt)
{
	Hero::hero->moveRight();
}