#pragma once
#ifndef HELPBUBBLE_H
#define HELPBUBBLE_H

#include "cocos2d.h"

class HelpBubble
{
public:
	HelpBubble(std::string filePath, cocos2d::Vec2 position, float a_startThreshold, float a_endThreshold);

	cocos2d::Sprite* sprite;
	//start and end thresholds for displaying the help bubble
	float startThreshold;
	float endThreshold;

	bool isFading;

	static std::vector<HelpBubble*> helpBubbleList;

	void update(float dt);
};
#endif