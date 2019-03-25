#include "Grapple.h"
#include "PlatformTile.h"
#include "GroundTile.h"

Grapple* Grapple::grapple = 0;

Grapple::Grapple() :
	MOVE_SPEED(800),
	isActive(false),
	isLatched(false),
	isHeroAtEndPoint(false),
	lengthScale(0),
	heroMoveScale(0),
	latchDuration(0)
{
}

//initializes the grapple and creates a single object for the class (if one doesn't already exist)
void Grapple::initGrapple()
{
	if (!grapple)
	{
		grapple = new Grapple;

		//set up repeating pattern sprite
		grapple->sprite = Sprite::create("Sprites/testGrapple.png");
		Texture2D::TexParams params;
		params.minFilter = GL_NEAREST;
		params.magFilter = GL_NEAREST;
		params.wrapS = GL_REPEAT;
		params.wrapT = GL_REPEAT;
		grapple->sprite->getTexture()->setTexParameters(params);
		grapple->sprite->setVisible(0);
		grapple->sprite->setAnchorPoint(Vec2(0.5f, 0.0f));

		//set up tip sprite
		grapple->tip = Sprite::create("Sprites/grappleTip.png");
		grapple->tip->setVisible(0);
		grapple->tip->setAnchorPoint(Vec2(0.f, 0.0f));
	}
}

//performs initial grapple shoot actions
void Grapple::shoot(Vect2 destination)
{
	if (!isActive)
	{
		//set all initial variables upon grapple being shot out
		isActive = true;
		initialPosClicked = destination;
		initialPosClicked.y -= 13;
		lastFrameGrappleTip = Vect2(Hero::hero->getPosition().x, Hero::hero->getPosition().y);

		//determine look position after latching
		if (Hero::hero->getPosition().x <= initialPosClicked.x)
		{
			Hero::hero->lookState = Hero::LookDirection::lookingRight;
			Hero::hero->arm->setZOrder(Hero::hero->sprite->getZOrder() - 1);
		}
		else //heroLatchPos.x > latchPoint.x
		{
			Hero::hero->lookState = Hero::LookDirection::lookingLeft;
			Hero::hero->arm->setZOrder(Hero::hero->sprite->getZOrder() -/*+*/ 1);
		}

		extendGrapple();

		//make arm visible and rotate it
		Hero::hero->arm->setVisible(1);
		Hero::hero->arm->setRotation(theta * 180 / M_PI);

		//make grapple sprite visible
		sprite->setVisible(1);
		grapple->tip->setVisible(1);
	}
}

//extends the grapple past the point the player aimed at
void Grapple::extendGrapple()
{
	//find the angle at which the grapple is being shot at
	Vect2 distance = initialPosClicked - Vect2(Hero::hero->getPosition().x, Hero::hero->getPosition().y); //calculate distance vector between the grapple and the hero
	theta = atan2(distance.x, distance.y); //perform atan2 (returns the angle in radians between the positive x axis (1, 0) and the point provided) on the distance

	//get normalized new endpoint
	Vect2 normalizedEndPoint(sin(theta), cos(theta));

	endPoint = normalizedEndPoint * 99999; //calculate new endpoint by extending the normalized version
}

//called when the grapple latches onto something
void Grapple::latch()
{
	isLatched = true;
	heroLatchPosition = Vect2(Hero::hero->getPosition().x, Hero::hero->getPosition().y);
	heroToLatchPointDistance = Vect2::calculateDistance(heroLatchPosition, latchPoint);

	//determine look position after latching
	if (heroLatchPosition.x <= latchPoint.x)
	{
		Hero::hero->lookState = Hero::LookDirection::lookingRight;
		Hero::hero->arm->setZOrder(Hero::hero->sprite->getZOrder() - 1);
	}
	else //heroLatchPos.x > latchPoint.x
	{
		Hero::hero->lookState = Hero::LookDirection::lookingLeft;
		Hero::hero->arm->setZOrder(Hero::hero->sprite->getZOrder() + 1);
	}
}

//grapple detaches and disappears, reset all values for the grapple
void Grapple::unLatch()
{
	Hero::hero->arm->setVisible(0); //make arm invisible
	sprite->setVisible(0);
	grapple->tip->setVisible(0);
	isActive = false;
	isLatched = false;
	isHeroAtEndPoint = false;
	//grapple->clear();
	lengthScale = 0;
	heroMoveScale = 0;
	latchDuration = 0;
}

//check for grapple hook max length or out of bounds
bool Grapple::isMaxLength()
{
	Vect2 grappleLength = grappleTip - Vect2(Hero::hero->getPosition().x, Hero::hero->getPosition().y);
	if (grappleLength.getMagnitude() > 500) //check max length
		return true;
	else if (grappleTip.x < 0 || grappleTip.x > GameObject::MAX_X || grappleTip.y < 0 || grappleTip.y > GameObject::MAX_Y) //check for out of bounds
		return true;

	return false;
}

/*//checks collision between the grapple and a game object
bool Grapple::isCollidingWith(GameObject* otherObject)
{
	if (grappleTip.x >= otherObject->getRightSidePos() || grappleTip.x <= otherObject->getLeftSidePos())
		return false;
	else if (grappleTip.y >= otherObject->getTopPos() || grappleTip.y <= otherObject->getBottomPos())
		return false;
	//if neither, there's a collision
	else
		return true;
}*/
bool Grapple::isCollidingWith(cocos2d::Rect otherObject)
{
	if (grappleTip.x >= otherObject.getMaxX() || grappleTip.x <= otherObject.getMinX())
		return false;
	else if (grappleTip.y >= otherObject.getMaxY() || grappleTip.y <= otherObject.getMinY())
		return false;
	//if neither, there's a collision
	else
		return true;
}

/*//performs collision detection with a given point to check
bool Grapple::checkPointCollision(Vect2 pointToCheck, GameObject * otherObject)
{
	if (pointToCheck.x >= otherObject->getRightSidePos() || pointToCheck.x <= otherObject->getLeftSidePos())
		return false;
	else if (pointToCheck.y >= otherObject->getTopPos() || pointToCheck.y <= otherObject->getBottomPos())
		return false;
	//if neither, there's a collision
	else
		return true;
}*/
bool Grapple::checkPointCollision(Vect2 pointToCheck, cocos2d::Rect otherObject)
{
	if (pointToCheck.x >= otherObject.getMaxX() || pointToCheck.x <= otherObject.getMinX())
		return false;
	else if (pointToCheck.y >= otherObject.getMaxY() || pointToCheck.y <= otherObject.getMinY())
		return false;
	//if neither, there's a collision
	else
		return true;
}

/*//performs collision detection that checks for multiple points per frame
bool Grapple::checkTunnelingCollision(GameObject* otherObject)
{
	Vect2 positionToCheck;
	for (float positionScale = 0.25f; positionScale < 1.0f; positionScale += 0.25f)
	{
		positionToCheck = Vect2::lerp(lastFrameGrappleTip, grappleTip, positionScale); //lerp along the distance travelled last frame 

		if (checkPointCollision(positionToCheck, otherObject)) //check for collision at the determined position
		{
			latchPoint = positionToCheck;
			grappleTip = latchPoint;
			return true;
		}
	}

	return false;
}*/
bool Grapple::checkTunnelingCollision(cocos2d::Rect otherObject)
{
	Vect2 positionToCheck;
	for (float positionScale = 0.25f; positionScale < 1.0f; positionScale += 0.25f)
	{
		positionToCheck = Vect2::lerp(lastFrameGrappleTip, grappleTip, positionScale); //lerp along the distance travelled last frame 

		if (checkPointCollision(positionToCheck, otherObject)) //check for collision at the determined position
		{
			latchPoint = positionToCheck;
			grappleTip = latchPoint;
			return true;
		}
	}

	return false;
}

void Grapple::update(float dt, Scene* scene)
{
	if (isActive)
	{
		startPoint = Vect2(Hero::hero->getPosition().x, Hero::hero->getPosition().y + 13); //have grapple start point move with the hero

		if (isLatched)
		{
			heroMoveScale += 25 / heroToLatchPointDistance;

			//check if the hero has reached the end of the grapple latch point
			if (heroMoveScale >= 1.0f)
			{
				Hero::hero->arm->setVisible(0); //make arm invisible
				sprite->setVisible(0);
				grapple->tip->setVisible(0);
				isHeroAtEndPoint = true;
				heroMoveScale = 1.0f;

				latchDuration += dt;
			}

			//move the hero to the new position, determined by lerping along the grapple
			Vect2 newHeroPosition = Vect2::lerp(heroLatchPosition, latchPoint, heroMoveScale);
			Hero::hero->sprite->setPosition(Vec2(newHeroPosition.x, newHeroPosition.y));
			Hero::hero->velocity.y = 0;

			//check to see if the hero has been latched for beyond the max duration
			if (latchDuration > 0.5f)
				unLatch();
		}
		else
		{
			extendGrapple(); //recalculate endpoint, ensuring that the initial mouse clicked position is passed through

			grappleTip = Vect2::lerp(startPoint, endPoint, lengthScale); //use lerp to increase the length of the grapple each frame until it reaches the end point

			heroToDestinationDistance = Vect2::calculateDistance(startPoint, endPoint);

			lengthScale += 35 / heroToDestinationDistance;

			//check for collision on each platform
			unsigned int numPlatforms = PlatformTile::platformTileList.size();
			for (unsigned int i = 0; i < numPlatforms; i++)
			{
				if (checkTunnelingCollision(PlatformTile::platformTileList[i]->hitBox))
				{
					latch();
					break;
				}
			}

			//check for collision on each ground tile
			unsigned int numGroundTiles = GroundTile::groundTileList.size();
			for (unsigned int i = 0; i < numGroundTiles; i++)
			{
				if (checkTunnelingCollision(GroundTile::groundTileList[i]->hitBox))
				{
					unLatch();
					break;
				}
			}

			//limit length scale factor to 1 (1 being the endpoint) or max length being reached
			if (lengthScale > 1.0f || isMaxLength())
				unLatch();

			lastFrameGrappleTip = grappleTip;
		}

		if (isActive)
		{
			float grappleDistance = Vect2::calculateDistance(startPoint, grappleTip);

			//show grapple sprite and rotate properly
			sprite->setTextureRect(cocos2d::Rect(startPoint.x, startPoint.y, 4, grappleDistance));
			sprite->setPosition(Vec2(startPoint.x, startPoint.y + 10));
			sprite->setRotation(theta * 180 / M_PI);

			//show grapple tip sprite and rotate properly
			tip->setPosition(Vec2(grappleTip.x, grappleTip.y + 16));
			tip->setRotation(theta * 180 / M_PI);
		}

		//rotate arm
		Hero::hero->arm->setRotation(theta * 180 / M_PI);
	}
}
