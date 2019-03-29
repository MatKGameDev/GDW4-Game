#include "myHelper.h"

myHelper::myHelper()
{
}

myHelper::~myHelper()
{
}

//checks AABB rect collision
bool myHelper::isCollision(cocos2d::Rect rect1, cocos2d::Rect rect2)
{
	//check x values to see if they arent touching
	//assuming rects are named A and B:
	//A_begin.x > B_end.x OR B_begin.x > A_end.x means there IS a gap on x
	if (rect1.getMinX() >= rect2.getMaxX() || rect2.getMinX() >= rect1.getMaxX())
		return false;
	//check y values to see if they arent touching
	//A_begin.y > B_end.y OR B_begin.y > A_end.y means there IS a gap on y
	else if (rect1.getMinY() >= rect2.getMaxY() || rect2.getMinY() >= rect1.getMaxY())
		return false;
	//if neither, there's a collision
	else
		return true;
}

cocos2d::Vec2 myHelper::getLineLineIntersect(cocos2d::Vec2 lineOneStart, cocos2d::Vec2 lineOneEnd, cocos2d::Vec2 lineTwoStart, cocos2d::Vec2 lineTwoEnd)
{
	return cocos2d::Vec2();
}

//gets a random number
int myHelper::getRandNum(int maxNum, int scaleNum, bool canBeNegative)
{
	int randNum = (rand() % maxNum) + scaleNum;

	//number can be a negative
	if (canBeNegative)
	{
		//check randomly for either a 1 or 0 to determine if number should be negative or not
		if (rand() % 2)
			randNum *= -1;
	}

	return randNum;
}

