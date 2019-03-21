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
	static int getRandNum(int maxNum, int scaleNum, bool canBeNegative = false);
};
#endif