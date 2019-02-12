#include "Hero.h"
#include "HeroAttackManager.h"

Hero* Hero::hero = 0;

Hero::Hero() : GameObject(Vect2(0, 0), "Sprites/Hero.png"),
	JUMP_VELOCITY(530),
	MAX_HORIZONTAL_VELOCITY(300),
	MAX_VERTICAL_VELOCITY(850), //900
	DRAG_VELOCITY(30),
	movespeedIncrease(20),
	isMovingLeft(false), 
	isMovingRight(false), 
	isAirborne(false)
{
	mass = 5;

	hurtBox.setRect(getLeftSidePos() + width / 3.0f, getBottomPos() + height / 6.0f, width / 4.0f, height / 1.5f);
}

void Hero::createHero()
{
	if (!hero)
		hero = new Hero;
}

void Hero::moveRight()
{
	velocity.x += movespeedIncrease;
}

void Hero::moveLeft()
{
	velocity.x -= movespeedIncrease;
}

//jump if not already airbourne
void Hero::jump()
{
	if (!isAirborne)
		velocity.y += JUMP_VELOCITY;
}

void Hero::updatePhysics(float dt)
{
	//check if airborne or not
	if (velocity.y == 0 || velocity.y == (GRAVITY.y * mass))
		isAirborne = false;
	else
		isAirborne = true;

	//check if moving downwards (increase gravity)
	if (velocity.y < 0)
		gravityMultiplier = 1.7f;
	else
		gravityMultiplier = 1.0f;

	this->GameObject::updatePhysics(dt); //call base class update

	//check for movement and apply drag if necessary
	if (isMovingRight)
		moveRight();
	else if (isMovingLeft)
		moveLeft();
	//no player input but hero is still moving
	else if (velocity.x > 0)
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
}

void Hero::update(float dt)
{
	this->updatePhysics(dt);

	hurtBox.setRect(getLeftSidePos() + width / 3.0f, getBottomPos() + height / 6.0f, width / 4.0f, height / 1.5f); //update the hurtbox location
	
	HeroAttackManager::update(dt);
}