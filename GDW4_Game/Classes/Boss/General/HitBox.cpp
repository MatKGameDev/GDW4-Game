#include "HitBox.h"

HitBox::HitBox(const cocos2d::Vec2& position, const float& aHeight, const float& aWidth)
	: height(aHeight), width(aWidth)
{
	updateHitBox(position);
}

void HitBox::updateHitBox(const cocos2d::Vec2& newPosition)
{
	//Update hit box
	hitBox.setRect(newPosition.x - width / 2, newPosition.y - height / 2, width, height);
}

void HitBox::setNewSize(const float& newWidth, const float& newHeight)
{
	width = newWidth;
	height = newHeight;
}

