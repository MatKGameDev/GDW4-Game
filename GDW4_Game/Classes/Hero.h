#pragma once
#ifndef HERO_H
#define HERO_H

#include "GameObject.h"
#include "Animation.h"

//singleton hero class
class Hero : public GameObject
{
public:
	const float JUMP_VELOCITY;
	const float MAX_HORIZONTAL_VELOCITY;
	const float MAX_VERTICAL_VELOCITY;
	const float DRAG_VELOCITY;

	static Hero* hero; //single hero instance
	
	void createHero();

	cocos2d::Sprite* arm;

	float movespeedIncrease;
	bool isAirborne;
	float invincibilityTimer;

	enum LookDirection
	{
		lookingRight,
		lookingLeft
	};
	LookDirection lookState;

	enum MoveDirection
	{
		idle,
		movingRight,
		movingLeft
	};
	MoveDirection moveState;

	int health;

	bool bypassSpeedCap;

	void moveRight();
	void moveLeft();
	void jump();

	void takeDamage(float sourcePositionX);
	void reset();

	void updateArmPosition();
	void updatePositionBasedOnArm();

	void checkAndResolveOutOfBounds();
	void updatePhysics(float dt) override;
	void updateHitboxes() override;
	void updateCollisions();
	void update(float dt);

private:
	Hero();
};

#endif