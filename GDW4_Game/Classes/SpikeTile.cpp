#include "SpikeTile.h"

std::vector<SpikeTile*> SpikeTile::spikeTileList = std::vector<SpikeTile*>();

SpikeTile::SpikeTile(cocos2d::Vec2 position, float tileSize)
	: TileBase(position, tileSize)
{
	hitBox.setRect(position.x, position.y, tileSize, tileSize);
	spikeTileList.push_back(this);
}

bool SpikeTile::checkAndResolveCollision(GameObject * otherObject)
{
	if (this->checkGeneralCollision(otherObject))
		return true;

	return false;
}