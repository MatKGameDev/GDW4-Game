#pragma once
#ifndef GRAPPLE_H
#define GRAPPLE_H

#include "cocos2d.h"
#include "Vect2.h"
#include "Platform.h"

class Grapple
{
private:
	Grapple();

public:
	static Grapple* grapple;
	void initGrapple();

	static const float MOVE_SPEED;
	static const float MAX_LENGTH;

	Sprite* sprite;
	Sprite* tip;
	Sprite* indicator;

	Vect2 initialPosClicked;
	Vect2 startPoint;
	Vect2 endPoint;
	Vect2 grappleTip;
	Vect2 lastFrameGrappleTip;
	Vect2 latchPoint;
	Vect2 heroLatchPosition;

	float lengthScale;
	float heroMoveScale;
	float theta;
	float latchDuration;

	float heroToLatchPointDistance;
	float heroToDestinationDistance;

	Color4F grappleColour;
	
	bool isActive;
	bool isLatched;
	bool isHeroAtEndPoint;

	void predictCollision();
	void shoot(Vect2 destination);
	void shoot(float a_theta);
	void extendGrapple();
	void latch();
	void unLatch();

	bool isMaxLength();
	void performGrapplePrediction();
	bool isCollidingWith(cocos2d::Rect otherObject);
	bool checkPointCollision(Vect2 pointToCheck, cocos2d::Rect otherObject);
	bool checkTunnelingCollision(cocos2d::Rect otherObject);
	bool checkAllPlatformCollisions();

	void update(float dt, Scene* scene);
};
#endif