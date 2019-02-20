#include "IceProjectile.h"
#include "Hero.h"
#include <iostream>

const float IceProjectile::SPEED = 900;
std::vector<IceProjectile*> IceProjectile::iceProjectileList = std::vector<IceProjectile*>();

//default sets velocity to 0
IceProjectile::IceProjectile() : GameObject(Hero::hero->getPosition(), "Sprites/IceProjectileTest.png")
{
	mass = 0;
	velocity = Vect2(0, 0);
	iceProjectileList.push_back(this);
}
//create projectile with starting velocity
IceProjectile::IceProjectile(Vect2 startVelocity) : GameObject(Hero::hero->getPosition(), "Sprites/IceProjectileTest.png")
{
	mass = 0;
	velocity = startVelocity;
	iceProjectileList.push_back(this);
}

void IceProjectile::removeAndDelete()
{
	//remove the ice projectile
	destroySprite();
	iceProjectileList.erase(std::remove(iceProjectileList.begin(), iceProjectileList.end(), this), iceProjectileList.end()); //remove from vector list
}

//checks if the projectile is out of bounds and performs appropriate actions
void IceProjectile::checkAndResolveOutOfBounds()
{
	//check for out of bounds
	//on x
	if (getLeftSidePos() < 0 || getRightSidePos() > MAX_X)
		removeAndDelete();
	//on y
	else if (getBottomPos() < 0 || getTopPos() > MAX_Y)
		removeAndDelete();
}

void IceProjectile::update(float dt)
{
	//call base update
	GameObject::updatePhysics(dt);

	checkAndResolveOutOfBounds();
}