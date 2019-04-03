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
	if (HudList.size() > 0)
	{
		if (Hero::hero->health < HudList.size())
		{
			HudList[Hero::hero->health]->sprite->setVisible(0);
			HudList.erase(HudList.begin() + Hero::hero->health);
		}
	}
	else if (Hero::hero->health <= 0)
	{
		HudList[0]->sprite->setVisible(0);
		HudList.erase(HudList.begin());
	}
}