#include "HelpBubble.h"
#include "Hero.h"

std::vector<HelpBubble*> HelpBubble::helpBubbleList = std::vector<HelpBubble*>();

HelpBubble::HelpBubble(std::string filePath, cocos2d::Vec2 position, float a_startThreshold, float a_endThreshold)
{
	//set up sprite
	sprite = Sprite::create(filePath);
	sprite->setPosition(position);
	sprite->setOpacity(0); //set opacity to 0 to allow fading in

	//set thresholds
	startThreshold = a_startThreshold;
	endThreshold = a_endThreshold;

	isFading = false;

	helpBubbleList.push_back(this); //add to list
}

//check hero's position to determine if we should doing any fading in/out
void HelpBubble::update(float dt)
{
	float heroPosX = Hero::hero->getPosition().x;

	//check if hero is in threshold range
	if (heroPosX > startThreshold && heroPosX < endThreshold && !isFading)
	{
		sprite->runAction(cocos2d::FadeIn::create(1));
		isFading = true;
	}
	//check if hero is out of threshold range and sprite is still visible
	else if ((heroPosX < startThreshold && sprite->getOpacity()) || (heroPosX > endThreshold && sprite->getOpacity()))
	{
		sprite->runAction(cocos2d::FadeOut::create(1));
		isFading = false;
	}
}