#pragma once

#include "cocos2d.h"

class myHelper
{
public:
	myHelper();
	virtual ~myHelper();

	static int getRandNum(int maxNum, int scaleNum, bool canBeNegative = false);
};