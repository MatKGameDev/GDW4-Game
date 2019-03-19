#pragma once
#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "cocos2d.h"
#include "Vect2.h"
#include "myHelper.h"

using namespace cocos2d;

class GameObject
{
public:
	GameObject(Vect2 position, std::string spriteFilePath);
	virtual ~GameObject();

	static float MAX_X;
	static float MAX_Y;
	float width;
	float height;
	float theta;
	float mass;
	float gravityMultiplier;

	Vect2 lastFramePosition;
	Vect2 velocity;
	Vect2 acceleration;
	Vect2 force;
	static const Vect2 GRAVITY;

	Sprite* sprite;

	cocos2d::Rect hurtBox;
	cocos2d::Rect moveBox; //like a hitbox but for movement and shit

	//get sprite position functions
	Vect2 getPosition();
	float getLeftSidePos();
	float getRightSidePos();
	float getBottomPos();
	float getTopPos();

	void destroySprite();
	bool isMovementCollision(GameObject* otherObject);
	bool isHitboxCollision(cocos2d::Rect otherHitbox);

	virtual void updateHitboxes() = 0;
	virtual void updatePhysics(float dt);
};
#endif