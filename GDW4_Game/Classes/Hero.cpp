#include "Hero.h"
#include "HeroAttackManager.h"
#include "HeroStateManager.h"
#include "TileBase.h"
#include <iostream>

Hero* Hero::hero = 0;

Hero::Hero() : GameObject(Vect2(700, 150), "Sprites/shooting_test.png"),
	JUMP_VELOCITY(575),
	MAX_HORIZONTAL_VELOCITY(300),
	MAX_VERTICAL_VELOCITY(850),
	DRAG_VELOCITY(30),
	movespeedIncrease(70),
	isAirborne(false),
	lookState(LookDirection::lookingRight),
	moveState(MoveDirection::idle)
{
	//initialize arm
	arm = cocos2d::Sprite::create("Sprites/testArm.png");
	arm->setAnchorPoint(Vec2(0.5f, 0.0f));

	mass = 5;					

	marcos::AnimationManager::init();
	//auto anim = AnimationCache::getInstance()->getAnimation("idle_right_animation_key");
	//auto action = Animate::create(anim);
	//this->sprite->runAction(RepeatForever::create(action));
	//TODO: its not gonna be like this later change it. //this triggers a breakpoint, read acess violation
	hurtBox.setRect(getLeftSidePos() + width / 2.7f, getBottomPos() + height / 6.0f, width / 4.5f, height / 1.5f);

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
	if (this->moveBox.getMinX() < 0.0f)
	{
		sprite->setPositionX(this->moveBox.size.width / 2.0f);
		velocity.x = 0.0f;
	}
	else if (this->moveBox.getMaxX() > MAX_X)
	{
		sprite->setPositionX(MAX_X - (this->moveBox.size.width / 2.0f) - 2);
		velocity.x = 0.0f;
	}
	//on y
	if (this->moveBox.getMinY() < 0.0f)
	{
		sprite->setPositionY(this->moveBox.size.height / 2.0f);
		velocity.y = 0.0f;
	}
	else if (this->moveBox.getMaxY() > MAX_Y)
	{
		sprite->setPositionY(MAX_Y - (this->moveBox.size.height / 2.0f));
		velocity.y = 0.0f;
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
	updateHitboxes();
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

	arm->setPosition(this->sprite->getPosition()); //update arm position each frame
	std::cout << "\nx: " << getPosition().x << " y: " << getPosition().y;
}