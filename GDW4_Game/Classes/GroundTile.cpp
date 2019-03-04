#include "GroundTile.h"
#include "GameObject.h"
#include "Vect2.h"

std::vector<GroundTile*> GroundTile::groundTileList = std::vector<GroundTile*>();

GroundTile::GroundTile(cocos2d::Vec2 position, float tileSize)
	: TileBase(position, tileSize)
{
	type = TileType::ground;

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
		float leftSideOverlap = abs(otherObject->getPosition().x - this->hitBox.getMinX());
		float rightSideOverlap = abs(otherObject->getPosition().x - this->hitBox.getMaxX());
		overlap.x = std::min(leftSideOverlap, rightSideOverlap);

		//get overlap on y
		float bottomOverlap = abs(otherObject->getPosition().y - this->hitBox.getMinY());
		float topOverlap = abs(otherObject->getPosition().y - this->hitBox.getMaxY());
		overlap.y = std::min(bottomOverlap, topOverlap);

		if (overlap.x < overlap.y) //overlap on x is more shallow, so we want to push the x back
		{
			otherObject->sprite->setPositionX(otherObject->lastFramePosition.x); //push the object back to its x position last frame
			otherObject->velocity.x = 0; //reset velocity after collision
		}
		else //overlap on y is more shallow, so we want to push the y back
		{
			otherObject->sprite->setPositionY(otherObject->lastFramePosition.y); //push the object back to its y position last frame
			otherObject->velocity.y = 0; //reset velocity after collision
		}
		return true; //because a collision happened (and we resolved it)
	}
}
