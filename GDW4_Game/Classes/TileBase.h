#pragma once
#ifndef TILEBASE_H
#define TILEBASE_H

#include "cocos2d.h"

class GameObject; //forward declare

enum TileType
{
	platform,
	ground,
	spike
};

//base class for a tile
class TileBase
{
public:
	TileBase(cocos2d::Vec2 position, float tileSize);

	static std::vector<TileBase*> tileList;
	static void deleteAllTiles();

	cocos2d::Rect hitBox;
	TileType type;

	bool checkGeneralCollision(GameObject* otherObject);
	virtual bool checkAndResolveCollision(GameObject* otherObject) = 0;
};
#endif