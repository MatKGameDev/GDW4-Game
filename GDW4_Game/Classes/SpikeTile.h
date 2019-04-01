#pragma once
#include "TileBase.h"

class SpikeTile : public TileBase
{
public:
	SpikeTile(cocos2d::Vec2 position, float tileSize);

	static std::vector<SpikeTile*> spikeTileList;

	bool checkAndResolveCollision(GameObject* otherObject) override;
};