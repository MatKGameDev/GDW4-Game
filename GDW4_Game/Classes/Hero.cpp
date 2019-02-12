#include "Hero.h"
#include "HeroAttackManager.h"

Hero* Hero::hero = 0;

Hero::Hero() : GameObject(Vect2(0, 0), "Sprites/shooting_test.png"),
	JUMP_VELOCITY(530),
	MAX_HORIZONTAL_VELOCITY(300),
	MAX_VERTICAL_VELOCITY(850), //900
	DRAG_VELOCITY(30),
	movespeedIncrease(20),
	isAirborne(false),
	moveState(MoveDirection::idle)
{
	mass = 5;					
	this->heroAnimation = new marcos::HeroAnimation(this->sprite);
	heroAnimation->m_HeroAnimation->runAnimation(); //TODO: its not gonna be like this later change it. //this triggers a breakpoint, read acess violation
	hurtBox.setRect(getLeftSidePos() + width / 3.0f, getBottomPos() + height / 6.0f, width / 4.0f, height / 1.5f);
}

void Hero::createHero()
{
	if (!hero)
		hero = new Hero;
}

void Hero::moveRight()
{
	heroAnimation->m_RunningAnimation.runAnimation();
	velocity.x += movespeedIncrease;
	lookState = LookDirection::lookingRight;


	//heroAnimation needs a run animation override

	// What should probably be done:
	// runAnimation acts as a manager, it takes in certain params from hero, mainly state, and handles all behind the scenes work, displays the animation
	// The one issue with setting it up this way is that I have no idea if it would even work with this level of inheritance, in order to get it to work, probably
	// going to have to make 2 classes rather than 12, don't think I can handle integrating 12 classes

	// Alternatively it can be done the way mario was done, where the animation is hidden in the class object and RunAnimation only manages one animation at a time 
	// Based on the context it is called
}

void Hero::moveLeft()
{
	velocity.x -= movespeedIncrease;
	lookState = LookDirection::lookingLeft;
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
	if (moveState == MoveDirection::movingRight)
		moveRight();
	else if (moveState == MoveDirection::movingLeft)
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