#include "Grapple.h"
#include "PlatformTile.h"
#include "GroundTile.h"
#include "XinputManager.h"
#include "HeroStateManager.h"

Grapple* Grapple::grapple = 0;

const float Grapple::MOVE_SPEED = 800.0f;
const float Grapple::MAX_LENGTH = 500.0f;

Grapple::Grapple() :
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
		grapple->sprite = Sprite::create("Sprites/grapple.png");
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

void Grapple::predictCollision()
{
	if (ControllerInput::isControllerUsed)
	{
		//use xinput stuff to get a more accurate reading on the stick input than cocos' controller support
		XinputManager::instance->update();
		XinputController* controller1 = XinputManager::instance->getController(0);
		Stick sticks[2];
		controller1->getSticks(sticks);

		//calculate angle (in radians) using atan2 with the right stick's y and x values
		float grappleAngle = atan2(sticks[RS].x, sticks[RS].y);

		//check if right stick is at rest (add a small buffer account for reading being slightly off or controller rest not being perfectly calibrated)
		if (sticks[RS].x < 0.1 && sticks[RS].x > -0.1 && sticks[RS].y <= 0.1f && sticks[RS].y > -0.1f)
		{
			//calculate angle (in radians) using atan2 with the right stick's y and x values
			grappleAngle = atan2(0.0f, 1.0f);
		}

		//calculate endpoint
		Vect2 normalizedEndPoint(sin(grappleAngle), cos(grappleAngle));
		endPoint = Vect2(Hero::hero->getPosition()) + (normalizedEndPoint * (MAX_LENGTH - 50)); //calculate endpoint by extending the normalized version

		Vec2 heroPosition = Hero::hero->arm->getPosition();

		//loop through each platform tile to check for intersects
		unsigned int tileListSize = PlatformTile::platformTileList.size();
		for (unsigned int i = 0; i < tileListSize; i++)
		{
			cocos2d::Vec2 platformStart = Vec2(PlatformTile::platformTileList[i]->hitBox.getMinX(), PlatformTile::platformTileList[i]->hitBox.getMidY());
			cocos2d::Vec2 platformEnd = Vec2(PlatformTile::platformTileList[i]->hitBox.getMaxX(), PlatformTile::platformTileList[i]->hitBox.getMidY());

			Vec2 intersectPoint = myHelper::getLineLineIntersect(
				heroPosition, 
				Vec2(endPoint.x, endPoint.y), 
				platformStart, 
				platformEnd);

			//there is an intersection
			if (intersectPoint != Vec2(0, 0))
			{
				bool isCollisionAlongLine = false;

				//we have to do collision checks now because there could be something inbetween
				unsigned int numPlatforms = PlatformTile::platformTileList.size();
				for (unsigned int j = 0; j < numPlatforms; j++)
				{
					//make sure we skip past the platform that's already been confirmed for collision
					if (!(PlatformTile::platformTileList[j] == PlatformTile::platformTileList[i]))
					{
						cocos2d::Vec2 otherPlatformStart = Vec2(PlatformTile::platformTileList[j]->hitBox.getMinX(), PlatformTile::platformTileList[j]->hitBox.getMidY());
						cocos2d::Vec2 otherPlatformEnd = Vec2(PlatformTile::platformTileList[j]->hitBox.getMaxX(), PlatformTile::platformTileList[j]->hitBox.getMidY());

						Vec2 blockingPoint = myHelper::getLineLineIntersect(
							heroPosition,
							intersectPoint,
							otherPlatformStart,
							otherPlatformEnd);

						//there is a platform blocking the grapple
						if (blockingPoint != Vec2(0, 0))
						{
							isCollisionAlongLine = true;
							break;
						}
					}
				}

				//no collision yet, lets go through the ground blocks
				if (!isCollisionAlongLine)
				{
					GroundTile* currentTile;
					unsigned int numGroundTiles = GroundTile::groundTileList.size();
					for (unsigned int i = 0; i < numGroundTiles; i++)
					{
						currentTile = GroundTile::groundTileList[i];
						//first lets check if the distance is out of range to quickly eliminate most blocks
						if (Vect2::calculateDistance(heroPosition, Vect2(currentTile->hitBox.getMidX(), currentTile->hitBox.getMidY())) < (MAX_LENGTH + 100))
						{
							//this part is a bit tricky, to efficiently calculate collision blocking the grapple from hitting the platform,
							//all we really need is 2 lines, one from the top left corner of the block to the bottom right, and one from the
							//bottom left corner to the top right, and then check if the grapple passed either of the lines

							//check top left to bottom right
							cocos2d::Vec2 blockTopLeft = Vec2(currentTile->hitBox.getMinX(), currentTile->hitBox.getMaxY());
							cocos2d::Vec2 blockBottomRight = Vec2(currentTile->hitBox.getMaxX(), currentTile->hitBox.getMinY());

							Vec2 groundBlockPoint1 = myHelper::getLineLineIntersect(
								heroPosition,
								intersectPoint,
								blockTopLeft,
								blockBottomRight);

							//check bottom left to top right
							cocos2d::Vec2 blockBottomLeft = Vec2(currentTile->hitBox.getMinX(), currentTile->hitBox.getMinY());
							cocos2d::Vec2 blockTopRight = Vec2(currentTile->hitBox.getMaxX(), currentTile->hitBox.getMaxY());

							Vec2 groundBlockPoint2 = myHelper::getLineLineIntersect(
								heroPosition,
								intersectPoint,
								blockBottomLeft,
								blockTopRight);

							//there is an intersection
							if (groundBlockPoint1 != Vec2(0, 0) || groundBlockPoint2 != Vec2(0, 0))
							{
								isCollisionAlongLine = true;
								break;
							}
						}
					}
				}

				//if there isnt anything blocking the two intersections
				if (!isCollisionAlongLine)
				{
					indicator->setPosition(intersectPoint);
					indicator->setVisible(1);
					endPoint = intersectPoint;
					break; //break out of loop if we find a connection
				}
			}
			else //there is no intersection with any platforms
				indicator->setVisible(0);
		}
	}
}

//performs initial grapple shoot actions from a destination (mouse position)
void Grapple::shoot(Vect2 destination)
{
	if (!isActive && HeroStateManager::currentState != HeroStateManager::dying)
	{
		//set all initial variables upon grapple being shot out
		isActive = true;
		initialPosClicked = destination;
		initialPosClicked.y -= 13;

		//determine look position after latching
		if (Hero::hero->getPosition().x <= initialPosClicked.x)
		{
			Hero::hero->lookState = Hero::LookDirection::lookingRight;
			Hero::hero->arm->setZOrder(Hero::hero->sprite->getZOrder() - 1);
		}
		else //heroLatchPos.x > latchPoint.x
		{
			Hero::hero->lookState = Hero::LookDirection::lookingLeft;
			Hero::hero->arm->setZOrder(Hero::hero->sprite->getZOrder() + 1);
		}
		lookDirectionOnShoot = Hero::hero->lookState;
		Hero::hero->updateArmPosition();
		lastFrameGrappleTip = Hero::hero->arm->getPosition();

		extendGrapple();
		initialPosClicked = endPoint;

		//make arm visible and rotate it
		Hero::hero->arm->setVisible(1);
		Hero::hero->arm->setRotation(theta * 180 / M_PI);

		//make grapple sprite visible
		sprite->setVisible(1);
		grapple->tip->setVisible(1);

		HeroStateManager::shootingGrapple->onEnter(); //put hero in grapple state
	}
}

//performs initial grapple shoot actions from an angle (controller stick)
void Grapple::shoot(float a_theta)
{
	if (!isActive && HeroStateManager::currentState != HeroStateManager::dying)
	{
		//set all initial variables upon grapple being shot out
		theta = a_theta;
		isActive = true;
		lastFrameGrappleTip = Hero::hero->arm->getPosition();

		//determine look position after latching
		if (theta > 0)
		{
			Hero::hero->lookState = Hero::LookDirection::lookingRight;
			Hero::hero->arm->setZOrder(Hero::hero->sprite->getZOrder() - 1);
		}
		else if (theta < 0)
		{
			Hero::hero->lookState = Hero::LookDirection::lookingLeft;
			Hero::hero->arm->setZOrder(Hero::hero->sprite->getZOrder() + 1);
		}
		else if (theta == 0 && Hero::hero->lookState == Hero::LookDirection::lookingRight)
			Hero::hero->arm->setZOrder(Hero::hero->sprite->getZOrder() - 1);
		else if (theta == 0 && Hero::hero->lookState == Hero::LookDirection::lookingLeft)
			Hero::hero->arm->setZOrder(Hero::hero->sprite->getZOrder() + 1);

		lookDirectionOnShoot = Hero::hero->lookState;

		initialPosClicked = endPoint;

		//make arm visible and rotate it
		Hero::hero->arm->setVisible(1);
		Hero::hero->arm->setRotation(theta * 180 / M_PI);

		//make grapple sprite visible
		sprite->setVisible(1);
		grapple->tip->setVisible(1);

		HeroStateManager::shootingGrapple->onEnter(); //put hero in grapple state
	}
}

//extends the grapple past the point the player aimed at
void Grapple::extendGrapple()
{
	//find the angle at which the grapple is being shot at
	Vect2 distance = initialPosClicked - Hero::hero->arm->getPosition(); //calculate distance vector between the grapple and the hero
	theta = atan2(distance.x, distance.y); //perform atan2 (returns the angle in radians between the positive x axis (1, 0) and the point provided) on the distance

	//get normalized new endpoint
	Vect2 normalizedEndPoint(sin(theta), cos(theta));

	endPoint = Vect2(Hero::hero->arm->getPosition()) + (normalizedEndPoint * MAX_LENGTH); //calculate new endpoint by extending the normalized version
}

//called when the grapple latches onto something
void Grapple::latch()
{
	isLatched = true;
	heroLatchPosition = Vect2(Hero::hero->arm->getPosition());
	heroToLatchPointDistance = Vect2::calculateDistance(heroLatchPosition, latchPoint);
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
	Vect2 grappleLength = grappleTip - Vect2(Hero::hero->arm->getPosition());
	if (grappleLength.getMagnitude() > MAX_LENGTH) //check max length
		return true;
	else if (grappleTip.x < 0 || grappleTip.x > GameObject::MAX_X || grappleTip.y < 0 || grappleTip.y > GameObject::MAX_Y) //check for out of bounds
		return true;

	return false;
}

//displays an indicator to the player if there is any point of collision with a platform along the direction currently aimed
void Grapple::performGrapplePrediction()
{

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

//goes through each tile looking for collision
bool Grapple::checkAllPlatformCollisions()
{
	//loop through each platform tile to check for intersects
	unsigned int tileListSize = PlatformTile::platformTileList.size();
	for (unsigned int i = 0; i < tileListSize; i++)
	{
		cocos2d::Vec2 platformStart = Vec2(PlatformTile::platformTileList[i]->hitBox.getMinX(), PlatformTile::platformTileList[i]->hitBox.getMidY());
		cocos2d::Vec2 platformEnd = Vec2(PlatformTile::platformTileList[i]->hitBox.getMaxX(), PlatformTile::platformTileList[i]->hitBox.getMidY());

		Vec2 intersectPoint = myHelper::getLineLineIntersect(
			Vec2(lastFrameGrappleTip.x, lastFrameGrappleTip.y),
			Vec2(grappleTip.x, grappleTip.y),
			platformStart,
			platformEnd);

		//there is an intersection
		if (intersectPoint != Vec2(0, 0))
		{
			latchPoint = intersectPoint;
			grappleTip = latchPoint;
			return true;
		}
	}

	return false; //no collision
}

void Grapple::update(float dt, Scene* scene)
{
	if (isActive)
	{
		tip->setScale(1.2f);
		//indicator->setVisible(0);
		startPoint = Vect2(Hero::hero->arm->getPosition()); //have grapple start point move with the hero

		if (isLatched)
		{
			heroMoveScale += 25 / heroToLatchPointDistance;

			//check if the hero has reached the end of the grapple latch point
			if (heroMoveScale >= 1.0f)
			{
				//hide grappling sprites
				Hero::hero->arm->setVisible(0);
				sprite->setVisible(0);
				grapple->tip->setVisible(0);
				indicator->setVisible(0);

				isHeroAtEndPoint = true;
				heroMoveScale = 1.0f;

				latchDuration += dt;
			}

			//move the hero to the new position, determined by lerping along the grapple
			Vect2 newHeroPosition = Vect2::lerp(heroLatchPosition, latchPoint, heroMoveScale);
			Hero::hero->arm->setPosition(Vec2(newHeroPosition.x, newHeroPosition.y));
			Hero::hero->updatePositionBasedOnArm();
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
			if (checkAllPlatformCollisions())
				latch();

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
			sprite->setAnchorPoint(Vec2(0.5f, 0.0f));
			sprite->setTextureRect(cocos2d::Rect(startPoint.x, startPoint.y, 4, grappleDistance));
			sprite->setPosition(Vec2(startPoint.x, startPoint.y));
			sprite->setRotation(theta * 180 / M_PI);

			//show grapple tip sprite and rotate properly
			tip->setPosition(Vec2(grappleTip.x, grappleTip.y));
			tip->setRotation(theta * 180 / M_PI);
		}

		//rotate arm
		Hero::hero->arm->setRotation(theta * 180 / M_PI);
	}
	else //grapple is inactive
		predictCollision();
}
