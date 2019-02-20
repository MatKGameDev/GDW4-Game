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

	cocos2d::Rect hurtBox;

	float movespeedIncrease;

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

	bool isAirborne;

	void moveRight();
	void moveLeft();
	void jump();

	void checkAndResolveOutOfBounds();
	void updatePhysics(float dt) override;
	void update(float dt);

private:
	Hero();
};

#endif