#include "HeroMoveLeft.h"
#include "Hero.h"

HeroMoveLeft::HeroMoveLeft()
{
}

void HeroMoveLeft::init()
{
	//do initial animation stuff here
}

void HeroMoveLeft::update(float dt)
{
	Hero::hero->moveLeft();
}