#include "Hero.h"
#include "HeroAttackManager.h"
#include "HeroMovementBase.h"

Hero* Hero::hero = 0;

Hero::Hero() : GameObject(Vect2(0, 0), "Sprites/shooting_test.png"),
	JUMP_VELOCITY(530),
	MAX_HORIZONTAL_VELOCITY(300),
	MAX_VERTICAL_VELOCITY(850), //900
	DRAG_VELOCITY(30),
	movespeedIncrease(90), //20
	isAirborne(false),
	lookState(LookDirection::lookingRight)
{
	mass = 5;					
	marcos::AnimationManager::init();
	auto anim = AnimationCache::getInstance()->getAnimation("running_animation_key");
	auto action = Animate::create(anim);
	this->sprite->runAction(RepeatForever::create(action));
	//TODO: its not gonna be like this later change it. //this triggers a breakpoint, read acess violation
	hurtBox.setRect(getLeftSidePos() + width / 2.7f, getBottomPos() + height / 6.0f, width / 4.5f, height / 1.5f);
}

void Hero::createHero()
{
	if (!hero)
		hero = new Hero;
}

void Hero::moveRight()
{
	lookState = LookDirection::lookingRight;
	velocity.x += movespeedIncrease;

	/*auto anim = AnimationCache::getInstance()->getAnimation("idle_animation_key");
	auto action = Animate::create(anim);
	hero->sprite->runAction(RepeatForever::create(action));*/

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
	lookState = LookDirection::lookingLeft;
	velocity.x -= movespeedIncrease;
}

//jump if not already airbourne
void Hero::jump()
{
	if (!isAirborne)
		velocity.y += JUMP_VELOCITY;
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
	if (velocity.y == 0 || velocity.y == (GRAVITY.y * mass))
		isAirborne = false;
	else
		isAirborne = true;

	//check if moving downwards (increase gravity)
	if (velocity.y < 0)
		gravityMultiplier = 1.7f;
	else
		gravityMultiplier = 1.0f;

	HeroMovementBase::currentState->update(dt);

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

void Hero::updateAnimations(float dt)
{
	/*if (moveState == idle)
	{
		hero->sprite->runAction(marcos::AnimationManager::m_IdleActionAnimation->clone());
	}*/
}

void Hero::update(float dt)
{
	this->updatePhysics(dt);

	hurtBox.setRect(getLeftSidePos() + width / 2.7f, getBottomPos() + height / 6.0f, width / 5.0f, height / 1.5f); //update the hurtbox location
	//this->updateAnimations(dt);
	
	HeroAttackManager::update(dt);
}