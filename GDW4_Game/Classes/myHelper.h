#pragma once
#ifndef MYHELPER_H
#define MYHELPER_H

#include "cocos2d.h"

class myHelper
{
public:
	myHelper();
	virtual ~myHelper();

	static bool isCollision(cocos2d::Rect rect1, cocos2d::Rect rect2);
	static cocos2d::Vec2 getLineLineIntersect(cocos2d::Vec2 lineOneStart, cocos2d::Vec2 lineOneEnd, cocos2d::Vec2 lineTwoStart, cocos2d::Vec2 lineTwoEnd);
	static int getRandNum(int maxNum, int scaleNum, bool canBeNegative = false);
};
#endif