#include "IceProjectile.h"
#include "Hero.h"
#include <iostream>

const float IceProjectile::SPEED = 500;
std::vector<IceProjectile*> IceProjectile::iceProjectileList = std::vector<IceProjectile*>();

IceProjectile::IceProjectile(Vect2 startVelocity) : GameObject(Hero::hero->getPosition(), "Sprites/IceProjectileTest.png")
{
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
	std::cout << "\nPROJECTILE: x: " << sprite->getPositionX() << " - y: " << sprite->getPositionY() << "\n\n";

	checkAndResolveOutOfBounds();
	std::cout << "\nPROJECTILE nx: " << sprite->getPositionX() << " - y: " << sprite->getPositionY() << "\n\n";

}