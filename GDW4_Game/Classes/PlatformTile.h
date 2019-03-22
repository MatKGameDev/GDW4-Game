#pragma once
#ifndef PLATFORMTILE_H
#define PLATFORMTILE_H

#include "TileBase.h"

class PlatformTile : public TileBase
{
public:
	PlatformTile(cocos2d::Vec2 position, float tileSize);

	static std::vector<PlatformTile*> platformTileList;

	bool checkAndResolveCollision(GameObject* otherObject) override;
};
#endif