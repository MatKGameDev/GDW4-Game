#include "Platform.h"

std::vector<Platform*> Platform::platformList = std::vector<Platform*>();

Platform::Platform(Vect2 position) : GameObject(position, "Sprites/Platform2.png")
{
	mass = 0;
	updateHitboxes();
	platformList.push_back(this);
}

//platforms have their own collision (since these are one-way platforms, you can go through the bottom but not the top)
bool Platform::checkOneWayCollision(GameObject* otherObject)
{
	//check for general collision, then make sure only the bottom of the other object is colliding, then make sure the other object is moving down
	if (this->isMovementCollision(otherObject) && otherObject->getBottomPos() >= this->getBottomPos() && otherObject->velocity.y <= 0)
		return true;

	return false;
}

void Platform::updateHitboxes()
{
	moveBox.setRect(getLeftSidePos(), getBottomPos(), width, height);
	hurtBox.setRect(getLeftSidePos(), getBottomPos(), width, height);
}

void Platform::update()
{
	if (this->checkOneWayCollision(Hero::hero))
	{
		Hero::hero->sprite->setPositionY(this->getTopPos() + Hero::hero->height / 2);
		Hero::hero->velocity.y = 0;
	}
}
