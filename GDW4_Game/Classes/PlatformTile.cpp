#include "PlatformTile.h"
#include "Hero.h"

std::vector<PlatformTile*> PlatformTile::platformTileList = std::vector<PlatformTile*>();

PlatformTile::PlatformTile(cocos2d::Vec2 position, float tileSize)
	: TileBase(position, tileSize)
{
	hitBox.setRect(position.x, position.y + tileSize - 30, tileSize, 15); //set the rect of platforms to only be the highest few pixels (for collision purposes)
	type = TileType::platform;

	platformTileList.push_back(this);
}

bool PlatformTile::checkAndResolveCollision(GameObject * otherObject)
{
	//check x values to see if they arent touching
	//assuming objects are named A and B:
	//A_begin.x > B_end.x OR B_begin.x > A_end.x means there IS a gap on x
	if (this->hitBox.getMinX() >= otherObject->moveBox.getMaxX() || otherObject->moveBox.getMinX() >= this->hitBox.getMaxX())
		return false;
	//check y values to see if they arent touching
	//A_begin.y > B_end.y OR B_begin.y > A_end.y means there IS a gap on y
	else if (this->hitBox.getMinY() >= otherObject->moveBox.getMaxY() || otherObject->moveBox.getMinY() >= this->hitBox.getMaxY())
		return false;
	//make sure only the bottom of the other object is colliding, then make sure the other object is moving down
	else if (otherObject->getBottomPos() >= this->hitBox.getMinY() && otherObject->velocity.y <= 0)
	{
		otherObject->sprite->setPositionY(this->hitBox.getMaxY() + Hero::hero->height / 2);
		otherObject->velocity.y = 0;
		return true;
	}
	else //no proper collision detected
		return false;
}