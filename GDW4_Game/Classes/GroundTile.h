#pragma once
#include "TileBase.h"

class GroundTile : public TileBase
{
public:
	GroundTile(cocos2d::Vec2 position, float tileSize);

	static std::vector<GroundTile*> groundTileList;

	bool ignoreLeftCollision;
	bool ignoreRightCollision;
	bool ignoreBottomCollision;
	bool ignoreTopCollision;

	bool checkAndResolveCollision(GameObject* otherObject) override;
};