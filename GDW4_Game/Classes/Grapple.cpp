#include "Grapple.h"

Grapple* Grapple::grapple = 0;

Grapple::Grapple() : DrawNode(),
	MOVE_SPEED(800),
	isActive(false),
	isLatched(false),
	isHeroAtEndPoint(false),
	lengthScale(0),
	heroMoveScale(0),
	latchDuration(0)
{
	Grapple::create(10.0f);
	grappleColour = Color4F(255, 255, 255, 1.0f); //set grapple colour
}

//initializes the grapple and creates a single object for the class (if one doesn't already exist)
void Grapple::initGrapple()
{
	if (!grapple)
	{
		grapple = new Grapple;
		grapple->DrawNode::init();
	}
}

//performs initial grapple shoot actions
void Grapple::shoot(Vect2 destination)
{
	if (!isActive)
	{
		isActive = true;
		endPoint = destination;
		lastFrameGrappleTip = Hero::hero->getPosition();
	}
}

//called when the grapple latches onto something
void Grapple::latch()
{
	isLatched = true;
	heroLatchPosition = Hero::hero->getPosition();
	heroToLatchPointDistance = Vect2::calculateDistance(heroLatchPosition, latchPoint);
}

//grapple detaches and disappears, reset all values for the grapple
void Grapple::unLatch()
{
	isActive = false;
	isLatched = false;
	isHeroAtEndPoint = false;
	grapple->clear();
	lengthScale = 0;
	heroMoveScale = 0;
	latchDuration = 0;
}

//checks collision between the grapple and a game object
bool Grapple::isCollidingWith(GameObject* otherObject)
{
	if (grappleTip.x >= otherObject->getRightSidePos() || grappleTip.x <= otherObject->getLeftSidePos())
		return false;
	else if (grappleTip.y >= otherObject->getTopPos() || grappleTip.y <= otherObject->getBottomPos())
		return false;
	//if neither, there's a collision
	else
		return true;
}

//performs collision detection with a given point to check
bool Grapple::checkPointCollision(Vect2 pointToCheck, GameObject * otherObject)
{
	if (pointToCheck.x >= otherObject->getRightSidePos() || pointToCheck.x <= otherObject->getLeftSidePos())
		return false;
	else if (pointToCheck.y >= otherObject->getTopPos() || pointToCheck.y <= otherObject->getBottomPos())
		return false;
	//if neither, there's a collision
	else
		return true;
}

//performs collision detection that checks for multiple points per frame
bool Grapple::checkTunnelingCollision(GameObject* otherObject)
{
	Vect2 positionToCheck;
	for (float positionScale = 0.25f; positionScale < 1.0f; positionScale += 0.25f)
	{
		positionToCheck = Vect2::lerp(lastFrameGrappleTip, grappleTip, positionScale);
		if (checkPointCollision(positionToCheck, otherObject))
		{
			latchPoint = positionToCheck;
			return true;
		}
	}

	return false;
}

void Grapple::update(float dt, Scene* scene)
{
	if (isActive)
	{
		grapple->clear(); //clear the drawn grapple before each frame
		startPoint = Hero::hero->getPosition(); //have grapple start point move with the hero

		if (isLatched)
		{
			heroMoveScale += 25 / heroToLatchPointDistance;

			Vect2 newHeroPosition = Vect2::lerp(heroLatchPosition, latchPoint, heroMoveScale);
			Hero::hero->sprite->setPosition(Vec2(newHeroPosition.x, newHeroPosition.y));

			//check if the hero has reached the end of the grapple latch point
			if (heroMoveScale > 1.0f)
			{
				isHeroAtEndPoint = true;
				heroMoveScale = 1.0f;
				Hero::hero->velocity.y = 0;

				if (latchDuration > 0.3f)
					unLatch();

				latchDuration += dt;
			}
		}
		else
		{
			grappleTip = Vect2::lerp(startPoint, endPoint, lengthScale); //use lerp to increase the length of the grapple each frame until it reaches the end point

			heroToDestinationDistance = Vect2::calculateDistance(startPoint, endPoint);

			lengthScale += 35 / heroToDestinationDistance;

			for (int i = 0; i < Platform::platformList.size(); i++)
			{
				if (checkTunnelingCollision(Platform::platformList[i]))
				{
					latch();
					break;
				}
			}
			//limit length scale factor to 1 (1 being the endpoint)
			if (lengthScale > 1.0f)
			{
				latchPoint = grappleTip;
				latch(); //for now call latch when it reaches max length, change later to be performed on collision
				lengthScale = 1.0f;
			}

			lastFrameGrappleTip = grappleTip;
		}

		if (isActive)
		{
			//draw grapple (start point, end point, colour)
			grapple->drawLine(Vec2(grapple->startPoint.x, grapple->startPoint.y),
				Vec2(grapple->grappleTip.x, grapple->grappleTip.y),
				grapple->grappleColour);
		}
	}
}
