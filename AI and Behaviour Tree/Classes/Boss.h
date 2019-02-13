#pragma once
#include "FirstBossState.h"
#include <2d/CCSprite.h>


class Boss1LavaAttack;

class Boss
{
private:
	FirstBossState *state{ nullptr };
	cocos2d::Sprite *bossSprite{ nullptr };
	std::vector<Boss1LavaAttack*> lavaList;
	const cocos2d::Vec2 mouthPosition;

public:
	Boss(/*Need a hero pointer*/);
	~Boss();

	//Setters
	virtual void setState(FirstBossState *newState);

	//Getters
	cocos2d::Sprite* getSprite()const;
	std::vector<Boss1LavaAttack*> getLavaList() const;
	cocos2d::Vec2 getMouthPosition()const;

	//State changes and update
	void update(const float &deltaT, const cocos2d::Vec2 &heroPosition);

	//Attack functions
	void spewLava();
	void activateFlameThrower();
	void shootSucker();

	//Utility functions
	void removeFromLavaList(Boss1LavaAttack *elementToRemove);
};

