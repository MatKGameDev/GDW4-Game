#include "GroundTile.h"
#include "GameObject.h"
#include "Vect2.h"
#include <iostream>

std::vector<GroundTile*> GroundTile::groundTileList = std::vector<GroundTile*>();

GroundTile::GroundTile(cocos2d::Vec2 position, float tileSize)
	: TileBase(position, tileSize),
	ignoreLeftCollision(false),
	ignoreRightCollision(false),
	ignoreBottomCollision(false),
	ignoreTopCollision(false)
{
	type = TileType::ground;
	hitBox.setRect(position.x, position.y, tileSize, tileSize - 15); //set the rect of platforms to exclude the top few pixels

	groundTileList.push_back(this);
}

bool GroundTile::checkAndResolveCollision(GameObject * otherObject)
{
	//first see if there is any collision in the first place
	if (!this->checkGeneralCollision(otherObject))
		return false;
	//there is collision. time to resolve it
	else
	{
		Vect2 overlap;
		bool ignoreX = false;
		bool ignoreY = false;

		//get overlap on x
   		float leftSideOverlap = abs(otherObject->moveBox.getMaxX() - this->hitBox.getMinX());
		float rightSideOverlap = abs(otherObject->moveBox.getMinX() - this->hitBox.getMaxX());
		overlap.x = std::min(leftSideOverlap, rightSideOverlap);

		//check for ignoring collision on x
		if ((otherObject->moveBox.getMidX() > this->hitBox.getMidX() && ignoreRightCollision) || (otherObject->moveBox.getMidX() < this->hitBox.getMidX() && ignoreLeftCollision))
			ignoreX = true;

		//get overlap on y
		float bottomOverlap = abs(otherObject->moveBox.getMaxY() - this->hitBox.getMinY());
		float topOverlap = abs(otherObject->moveBox.getMinY() - this->hitBox.getMaxY());
		overlap.y = std::min(bottomOverlap, topOverlap);

		//check for ignoring collision on y
		if ((otherObject->moveBox.getMidY() > this->hitBox.getMidY() && ignoreTopCollision) || (otherObject->moveBox.getMidY() < this->hitBox.getMidY() && ignoreBottomCollision))
			ignoreY = true;

		if (overlap.y < overlap.x && !ignoreY) //overlap on y is more shallow, so we want to push the y back or if the object is at the top of the tile
		{
			if (bottomOverlap < topOverlap) //bottom is the shallow collision side
			{
				otherObject->sprite->setPositionY(otherObject->getPosition().y - overlap.y);
				otherObject->velocity.y = 0; //reset velocity after collision
			}
			else if (otherObject->velocity.y <= 0) //top side is the shallow collision side
			{
				otherObject->sprite->setPositionY(this->hitBox.getMaxY() + (otherObject->moveBox.size.height / 2));
				otherObject->velocity.y = 0; //reset velocity after collision
			}
		}
		else if (!ignoreX) //overlap on x is more shallow, so we want to push the x back
		{
			if (leftSideOverlap < rightSideOverlap) //left is the shallow collision side
				otherObject->sprite->setPositionX(this->hitBox.getMinX() - (otherObject->moveBox.size.width / 2) - 1);
			else //right side is the shallow collision side
				otherObject->sprite->setPositionX(this->hitBox.getMaxX() + (otherObject->moveBox.size.width / 2));

			//otherObject->sprite->setPositionX(otherObject->lastFramePosition.x); //push the object back to its x position last frame

			otherObject->velocity.x = 0; //reset velocity after collision
		}
		return true; //because a collision happened (and we resolved it)
	}
}
