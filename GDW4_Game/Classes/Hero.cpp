#include "Hero.h"
#include "HeroAttackManager.h"
#include "HeroStateManager.h"
#include "TileBase.h"
#include <iostream>

Hero* Hero::hero = 0;

Hero::Hero() : GameObject(Vect2(700, 0), "Sprites/shooting_test.png"),
	JUMP_VELOCITY(550),
	MAX_HORIZONTAL_VELOCITY(300),
	MAX_VERTICAL_VELOCITY(850),
	DRAG_VELOCITY(30),
	movespeedIncrease(70),
	isAirborne(false),
	lookState(LookDirection::lookingRight),
	moveState(MoveDirection::idle)
{
	mass = 5;					

	marcos::AnimationManager::init();

	updateHitboxes();
}

void Hero::createHero()
{
	if (!hero)
		hero = new Hero;
}

void Hero::moveRight()
{

	if (isAirborne)
		velocity.x += movespeedIncrease * 0.7; //add some drag in the air
	else
		velocity.x += movespeedIncrease;
}

void Hero::moveLeft()
{
	if (isAirborne)
		velocity.x -= movespeedIncrease * 0.7; //add some drag in the air
	else
		velocity.x -= movespeedIncrease;
}

//jump if not already airbourne
void Hero::jump()
{
	if (!isAirborne)
		velocity.y = JUMP_VELOCITY;
}

//checks if the character is out of bounds and performs appropriate actions
void Hero::checkAndResolveOutOfBounds()
{
	//check for out of bounds
	//on x
	if (this->getLeftSidePos() < 0)
	{
		sprite->setPositionX(this->width / 2);
		velocity.x = 0;
	}
	else if (this->getRightSidePos() > MAX_X)
	{
		sprite->setPositionX(MAX_X - this->width / 2);
		velocity.x = 0;
	}
	//on y
	if (this->getBottomPos() < 0)
	{
		sprite->setPositionY(this->height / 2);
		velocity.y = 0;
	}
	else if (this->getTopPos() > MAX_Y)
	{
		sprite->setPositionY(MAX_Y - this->height / 2);
		velocity.y = 0;
	}
}

void Hero::updatePhysics(float dt)
{
	//check if airborne or not
	if (velocity.y == 0)
		isAirborne = false;
	else
		isAirborne = true;

	HeroStateManager::currentState->update(dt);

	//have hero fall faster than rise
	if (velocity.y < 0)
		gravityMultiplier = 1.7f;
	else
		gravityMultiplier = 1.0f;


	this->GameObject::updatePhysics(dt); //call base class update

	//no player input but hero is still moving
	if (velocity.x > 0)
	{
		velocity.x -= DRAG_VELOCITY; //apply drag
	}
	else //velocity <= 0
	{
		velocity.x += DRAG_VELOCITY;

		//if velocity goes from negative to positive after drag is applied, set it to 0 to prevent a slight "drift" to occur in later frames if no movement key is pressed
		if (velocity.x > 0)
			velocity.x = 0;
	}

	//check max velocity
	//for x
	if (velocity.x > MAX_HORIZONTAL_VELOCITY) 
		velocity.x = MAX_HORIZONTAL_VELOCITY;
	else if (velocity.x < -MAX_HORIZONTAL_VELOCITY)
		velocity.x = -MAX_HORIZONTAL_VELOCITY;
	//for y
	if (velocity.y > MAX_VERTICAL_VELOCITY)
		velocity.y = MAX_VERTICAL_VELOCITY;
	else if (velocity.y < -MAX_VERTICAL_VELOCITY)
		velocity.y = -MAX_VERTICAL_VELOCITY;

	//check for hero out of bounds
	checkAndResolveOutOfBounds();
}

void Hero::updateHitboxes()
{
	moveBox.setRect(getLeftSidePos() + width / 5.0f, getBottomPos(), width / 1.6f, height);
	hurtBox.setRect(getLeftSidePos() + width / 2.7f, getBottomPos() + height / 6.0f, width / 4.5f, height / 1.5f);
}

//updates any collisions dealing with the hero and other objects
void Hero::updateCollisions()
{
	unsigned int tileListSize = TileBase::tileList.size();
	for (unsigned int i = 0; i < tileListSize; i++)
		TileBase::tileList[i]->checkAndResolveCollision(this);
}

//updates all the things
void Hero::update(float dt)
{
	this->updatePhysics(dt);

	updateHitboxes();
	updateCollisions();
	HeroAttackManager::update(dt);
}