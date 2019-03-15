#pragma once
#include "FirstBossState.h"
#include <2d/CCSprite.h>
#include "Boss1Attack.h"
#include "HitBox.h"

class Hero;

class Boss
{
private:
	FirstBossState *state{ nullptr };
	cocos2d::Sprite *bossSprite{ nullptr };
	std::vector<Boss1LavaAttack*> lavaList;
	const cocos2d::Vec2 mouthPosition;
	cocos2d::Scene *bossScene;
	HitBox hitBox;
	Hero* heroPointer;

public:
	Boss(Hero* heroInstance, cocos2d::Scene *sceneForBoss, float height = 581, float width = 315);
	~Boss();

	//Setters
	void setState(FirstBossState *newState);

	//Getters
	cocos2d::Sprite* getSprite()const;
	std::vector<Boss1LavaAttack*> getLavaList() const;
	cocos2d::Vec2 getMouthPosition()const;
	cocos2d::Scene* getBossScene() const;
	cocos2d::Rect getHitBox() const;

	//State changes and update
	void update(const float &deltaT, const cocos2d::Vec2 &heroPosition);

	//Attack functions
	void spewLava();
	void activateFlameThrower();
	void shootSucker();

	//Utility functions
	void removeFromLavaList(Boss1LavaAttack *elementToRemove);
};

