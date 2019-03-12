#pragma once
#include "TileBase.h"

class PlatformTile : public TileBase
{
public:
	PlatformTile(cocos2d::Vec2 position, float tileSize);

	static std::vector<PlatformTile*> platformTileList;

	bool checkAndResolveCollision(GameObject* otherObject) override;
};