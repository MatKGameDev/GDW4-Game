#include "Hero.h"
#include "HeroAttackManager.h"
#include "HeroStateManager.h"
#include "TileBase.h"
#include "Grapple.h"

Hero* Hero::hero = 0;

Hero::Hero() : GameObject(Vect2(700, 150), "Sprites/shooting_test.png"),
	JUMP_VELOCITY(610),
	MAX_HORIZONTAL_VELOCITY(300),
	MAX_VERTICAL_VELOCITY(850),
	DRAG_VELOCITY(30),
	movespeedIncrease(70),
	invincibilityTimer(0),
	health(3),
	isAirborne(false),
	bypassSpeedCap(false),
	lookState(LookDirection::lookingRight),
	moveState(MoveDirection::idle)
{
	//initialize arm
	arm = cocos2d::Sprite::create("Sprites/armV2.png");

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
	lookState = LookDirection::lookingRight;

	//make sure hero isn't above max velocity
	if (!(velocity.x > MAX_HORIZONTAL_VELOCITY || velocity.x < -MAX_HORIZONTAL_VELOCITY))
	{
		if (isAirborne)
			velocity.x += movespeedIncrease * 0.7; //add some drag in the air
		else
			velocity.x += movespeedIncrease;
	}
}

void Hero::moveLeft()
{
	lookState = LookDirection::lookingLeft;

	//make sure hero isn't above max velocity
	if (!(velocity.x > MAX_HORIZONTAL_VELOCITY || velocity.x < -MAX_HORIZONTAL_VELOCITY))
	{
		if (isAirborne)
			velocity.x -= movespeedIncrease * 0.7; //add some drag in the air
		else
			velocity.x -= movespeedIncrease;
	}
}

//jump if not already airbourne
void Hero::jump()
{
	if (!isAirborne)
		velocity.y = JUMP_VELOCITY;
}

//hero takes damage from any source
void Hero::takeDamage(float sourcePositionX)
{
	//make sure hero isn't already invulnerable or ded
	if (invincibilityTimer <= 0 && HeroStateManager::currentState != HeroStateManager::dying)
	{
		health--;
		invincibilityTimer = 0.99;

		bypassSpeedCap = true;

		//if we're not in any of the grappling states or dying, go into falling state
		if (HeroStateManager::currentState != HeroStateManager::grappling &&
			HeroStateManager::currentState != HeroStateManager::shootingGrapple &&
			HeroStateManager::currentState != HeroStateManager::holdingPlatform)
		{
			HeroStateManager::falling->onEnter();
		}
		
		if (this->getPosition().x < sourcePositionX)
			Hero::hero->velocity = Vect2(-600, 400);
		else //hero position().x <= sourcePositionX
			Hero::hero->velocity = Vect2(600, 400);
	}
}

//resets hero after a death or victory
void Hero::reset()
{
	invincibilityTimer = 0.0f;
	velocity = Vect2(0, 0);
	force = Vect2(0, 0);
	moveState = MoveDirection::idle;
	HeroStateManager::idle->onEnter();
	Grapple::grapple->unLatch();
	health = 3;
}

//updates the hero's arm position (only visible while grappling)
void Hero::updateArmPosition()
{
	float armRightOffset = 23;
	float armLeftOffset = 30;
	float armYOffset = 25;
	if (Grapple::grapple->lookDirectionOnShoot == LookDirection::lookingRight)
		arm->setPosition(Vec2(this->getPosition().x - armRightOffset, this->getPosition().y + armYOffset)); //update arm position each frame
	else //hero looking left
		arm->setPosition(Vec2(this->getPosition().x + armLeftOffset, this->getPosition().y + armYOffset)); //update arm position each frame
}

void Hero::updatePositionBasedOnArm()
{
	float armRightOffset = 23;
	float armLeftOffset = 30;
	float armYOffset = 25;
	if (Grapple::grapple->lookDirectionOnShoot == LookDirection::lookingRight)
		this->sprite->setPosition(Vec2(arm->getPosition().x + armRightOffset, arm->getPosition().y - armYOffset)); //update hero based on arm position when being pulled in
	else //hero looking left
		this->sprite->setPosition(Vec2(arm->getPosition().x - armLeftOffset, arm->getPosition().y - armYOffset)); //update hero based on arm position when being pulled in
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
	if (!bypassSpeedCap)
	{
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
	if (HeroStateManager::currentState != HeroStateManager::grappling)
	{
		unsigned int tileListSize = TileBase::tileList.size();
		for (unsigned int i = 0; i < tileListSize; i++)
		{
			//check if it's a spike tile (deals damage)
			if (TileBase::tileList[i]->checkAndResolveCollision(this) && TileBase::tileList[i]->type == TileType::spike)
			{
				this->takeDamage(TileBase::tileList[i]->hitBox.getMidX());
				this->health++;
			}
		}
	}
}

//updates all the things
void Hero::update(float dt)
{
	this->updatePhysics(dt);

	//check for invincibility
	if (((int)(invincibilityTimer * 10)) % 2 == 1)
		sprite->setVisible(0); //flicker the sprite
	else
		sprite->setVisible(1); //show the sprite again

	//update invincibility timer
	if (invincibilityTimer > 0)
	{
		invincibilityTimer -= dt;
		if (invincibilityTimer < 0.8f)
			bypassSpeedCap = false;
	}

	updateHitboxes();
	updateCollisions();
	HeroAttackManager::update(dt);
	updateArmPosition();

	//show grapple sprite and rotate properly
	Grapple::grapple->startPoint = Vect2(arm->getPosition()); //have grapple start point move with the hero
	float grappleDistance = Vect2::calculateDistance(Grapple::grapple->startPoint, Grapple::grapple->grappleTip);
	Grapple::grapple->sprite->setTextureRect(cocos2d::Rect(Grapple::grapple->startPoint.x, Grapple::grapple->startPoint.y, 4, grappleDistance));
	Grapple::grapple->sprite->setPosition(Vec2(Grapple::grapple->startPoint.x, Grapple::grapple->startPoint.y));
}