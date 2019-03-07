#pragma once
#include "cocos2d.h"
#include "Vect2.h"
#include "Platform.h"

class Grapple : public cocos2d::DrawNode
{
private:
	Grapple();

public:
	static Grapple* grapple;
	void initGrapple();

	const float MOVE_SPEED;

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

	void shoot(Vect2 destination);
	void latch();
	void unLatch();

	bool isCollidingWith(cocos2d::Rect otherObject);
	bool checkPointCollision(Vect2 pointToCheck, cocos2d::Rect otherObject);
	bool checkTunnelingCollision(cocos2d::Rect otherObject);

	void update(float dt, Scene* scene);
};