#include "HitBox.h"


HitBox::HitBox(cocos2d::Scene* aScene, float aHeight, float aWidth)
	: hitBoxShape(cocos2d::DrawNode::create()),height(aHeight), width(aWidth), scene(aScene)
{
	scene->addChild(hitBoxShape,1);
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

