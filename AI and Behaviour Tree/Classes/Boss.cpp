#include "Boss.h"
#include "Boss1Attack.h" 

Boss::Boss() : bossSprite(cocos2d::Sprite::create("Boss1.png")), mouthPosition(100, 500)
{
	state = new Idling4FirstBoss;
}

Boss::~Boss()
{
	delete state;
}

void Boss::setState(FirstBossState* newState)
{
	if (state != nullptr)
		delete state;
	state = newState;
}

cocos2d::Sprite* Boss::getSprite() const
{
	return bossSprite;
}

std::vector<Boss1LavaAttack*> Boss::getLavaList() const
{
	return lavaList;
}

cocos2d::Vec2 Boss::getMouthPosition() const
{
	return mouthPosition;
}

void Boss::update(const float &deltaT, const cocos2d::Vec2 &heroPosition)
{
	state->update(deltaT, this);
	for (size_t i = 0; i < lavaList.size(); i++)
	{
		try {
			lavaList[i]->update(deltaT);
		}
		catch (...)
		{
			lavaList.erase(lavaList.begin() + i);
		}
	}
}

void Boss::spewLava()
{
	for (size_t i = 1; i <= 3; i++) 
	{
		auto tempLavaBall = new LavaBall(cocos2d::Vec2(1000, 0),i, this);
		lavaList.push_back(tempLavaBall);
	}
}

void Boss::activateFlameThrower()
{
	lavaList.push_back(new FlameThrower(this));
}

void Boss::shootSucker()
{
	auto tempBullet = new SuckerBullet(cocos2d::Vec2(1000, 0), this);
	lavaList.push_back(tempBullet);
}

void Boss::removeFromLavaList(Boss1LavaAttack* elementToRemove)
{
	for (size_t i = 0; i < lavaList.size(); i++)
	{
		if (lavaList[i] == elementToRemove)
			lavaList.erase(lavaList.begin() + i);
	}
}
