#include "HitBox.h"

HitBox::HitBox(const cocos2d::Vec2& position, const float& aHeight, const float& aWidth, cocos2d::Scene* aScene)
	: hitBoxShape(cocos2d::DrawNode::create()), height(aHeight), width(aWidth), scene(aScene)
{
	scene->addChild(hitBoxShape, 50);
	updateHitBox(position);
}

HitBox::~HitBox()
{
	scene->removeChild(hitBoxShape);
}

void HitBox::updateHitBox(const cocos2d::Vec2& newPosition)
{
	//Update hit box
	hitBox.setRect(newPosition.x - width / 2, newPosition.y - height / 2, width, height);

	//Redraw the rect
	hitBoxShape->clear();
	hitBoxShape->drawRect(cocos2d::Vec2(hitBox.getMinX(), hitBox.getMinY()), cocos2d::Vec2(hitBox.getMaxX(), hitBox.getMaxY()), cocos2d::Color4F(0.0f, 1.0f, 0.0f, 1.0f));
}

void HitBox::setNewSize(const float& newWidth, const float& newHeight)
{
	width = newWidth;
	height = newHeight;
}

