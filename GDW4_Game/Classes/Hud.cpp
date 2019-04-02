#include "Hud.h"
#include "Hero.h"

std::vector<HudObject*> HudObject::HudList = std::vector<HudObject*>();

HudObject::~HudObject()
{
	
}

void HudObject::deleteAllInstances()
{
	HudList.clear();
}

HudObject::HudObject(std::string filePath, cocos2d::Vec2 position)
{
	//set up sprite
	sprite = cocos2d::Sprite::create(filePath);
	sprite->setPosition(position);

	HudList.push_back(this); //add to list
}

void HudObject::update(float dt)
{
		if (Hero::hero->getPosition().x > 1920 / 2)
		{
			//do some simple math to convert mouse click position on screen to in-game world position
			sprite->setPositionX(sprite->getPosition().x - 1920 / 2);
			sprite->setPositionX(sprite->getPosition().x + Hero::hero->sprite->getPosition().x);
		}
}