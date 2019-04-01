#include "TileBase.h"
#include "PlatformTile.h"
#include "GroundTile.h"
#include "SpikeTile.h"
#include "Hero.h"

std::vector<TileBase*> TileBase::tileList = std::vector<TileBase*>();

TileBase::TileBase(cocos2d::Vec2 position, float tileSize)
{
	hitBox.setRect(position.x, position.y, tileSize, tileSize);
	tileList.push_back(this);
}

//clears all tile vectors
void TileBase::deleteAllTiles()
{
	tileList.clear();
	PlatformTile::platformTileList.clear();
	GroundTile::groundTileList.clear();
	SpikeTile::spikeTileList.clear();
}

bool TileBase::checkGeneralCollision(GameObject * otherObject)
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
	else //no gap means collision!
		return true;
}
