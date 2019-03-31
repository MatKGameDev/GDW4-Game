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

//p1 = first line start point
//p2 = first line end point
//p3 = second line start point
//p4 = second line end point
cocos2d::Vec2 myHelper::getLineLineIntersect(cocos2d::Vec2 p1, cocos2d::Vec2 p2, cocos2d::Vec2 p3, cocos2d::Vec2 p4)
{
	float determinant = (p1.x - p2.x) * (p3.y - p4.y) - (p1.y - p2.y) * (p3.x - p4.x);
	//if determinant is 0, they're parallel
	if (determinant == 0) 
		return cocos2d::Vec2(0, 0);

	//get the x and y of the intersect
	float pre = p1.x * p2.y - p1.y * p2.x;
	float post = p3.x * p4.y - p3.y * p4.x;
	float x = (pre * (p3.x - p4.x) - (p1.x - p2.x) * post) / determinant;
	float y = (pre * (p3.y - p4.y) - (p1.y - p2.y) * post) / determinant;

	//check if the x and y coordinates are within both lines (add a small buffer to prevent rounding inaccuracies)
	if ((x + 0.01) < std::min(p1.x, p2.x) || (x - 0.01) > std::max(p1.x, p2.x) || (x + 0.01) < std::min(p3.x, p4.x) || (x - 0.01) > std::max(p3.x, p4.x)) 
		return cocos2d::Vec2(0, 0);

	if ((y + 0.01) < std::min(p1.y, p2.y) || (y - 0.01) > std::max(p1.y, p2.y) || (y + 0.01) < std::min(p3.y, p4.y) || (y - 0.01) > std::max(p3.y, p4.y))
		return cocos2d::Vec2(0, 0);

	//return the point of intersection
	cocos2d::Vec2 intersect = cocos2d::Vec2(x, y);
	return intersect;
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

