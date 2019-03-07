#include "GroundTile.h"
#include "GameObject.h"
#include "Vect2.h"

std::vector<GroundTile*> GroundTile::groundTileList = std::vector<GroundTile*>();

GroundTile::GroundTile(cocos2d::Vec2 position, float tileSize)
	: TileBase(position, tileSize)
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

		//get overlap on x
   		float leftSideOverlap = abs(otherObject->moveBox.getMaxX() - this->hitBox.getMinX());
		float rightSideOverlap = abs(otherObject->moveBox.getMinX() - this->hitBox.getMaxX());
		overlap.x = std::min(leftSideOverlap, rightSideOverlap);

		//get overlap on y
		float bottomOverlap = abs(otherObject->moveBox.getMaxY() - this->hitBox.getMinY());
		float topOverlap = abs(otherObject->moveBox.getMinY() - this->hitBox.getMaxY());
		overlap.y = std::min(bottomOverlap, topOverlap);

		if (overlap.x < overlap.y) //overlap on x is more shallow, so we want to push the x back
		{
			if (leftSideOverlap < rightSideOverlap) //left is the shallow side
				otherObject->sprite->setPositionX(otherObject->getPosition().x - overlap.x);
			else //right side is the shallow side
				otherObject->sprite->setPositionX(otherObject->getPosition().x + overlap.x);
			//otherObject->sprite->setPositionX(otherObject->lastFramePosition.x); //push the object back to its x position last frame
			otherObject->velocity.x = 0; //reset velocity after collision
		}
		else //overlap on y is more shallow, so we want to push the y back
		{
			if (bottomOverlap < topOverlap) //bottom is the shallow side
				otherObject->sprite->setPositionY(otherObject->getPosition().y - overlap.y);
			else //top side is the shallow side
				otherObject->sprite->setPositionY(otherObject->getPosition().y + overlap.y);

			otherObject->velocity.y = 0; //reset velocity after collision
		}
		return true; //because a collision happened (and we resolved it)
	}
}
