#pragma once
#include "cocos2d.h"
#include "Vect2.h"
#include "myHelper.h"

using namespace cocos2d;

class GameObject
{
public:
	GameObject(Vect2 position, std::string spriteFilePath);
	virtual ~GameObject();

	static const float MAX_X;
	static const float MAX_Y;
	float width;
	float height;
	float theta;
	float mass;
	float gravityMultiplier;

	Vect2 velocity;
	Vect2 acceleration;
	Vect2 force;
	static const Vect2 GRAVITY;

	Sprite* sprite;

	//get sprite position functions
	Vect2 getPosition();
	float getLeftSidePos();
	float getRightSidePos();
	float getBottomPos();
	float getTopPos();

	void destroySprite();
	bool isCollidingWith(GameObject* otherObject);

	virtual void updatePhysics(float dt);
};