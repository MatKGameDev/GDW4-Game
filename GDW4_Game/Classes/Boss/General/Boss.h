#pragma once

//Header Files
#include <2d/CCSprite.h>
#include "HitBox.h"
#include "Boss/Ability States/FirstBossState.h"
#include "Animation.h"

//Foward Declare Classes
class Hero;
class Boss1LavaAttack;


class Boss
{
private:
	int health;
	FirstBossState *state;
	cocos2d::Sprite *bossSprite;
	std::vector<Boss1LavaAttack*> lavaList;
	cocos2d::Scene *bossScene;
	std::vector<HitBox*> hitboxList;
	HitBox* hitBox;
	Hero* heroPointer;

	//Private Utility functions
	void initHitbox();

public:
	Boss(Hero* heroInstance, cocos2d::Scene *sceneForBoss, float height = 581, float width = 325);
	~Boss();

	//Setters
	void setState(FirstBossState *newState);

	//Getters
	int getHealth() const;
	cocos2d::Sprite* getSprite() const;
	std::vector<Boss1LavaAttack*> getLavaList() const;
	cocos2d::Scene* getBossScene() const;
	cocos2d::Rect getHitBox() const;
	FirstBossState* getCurrentState() const;

	//Member functions
	void takeDamage();
	void update(const float &deltaT);
	

	//Attack functions
	void spewLava();
	void activateFlameThrower();
	void shootExplosiveBullet();

	//Utility functions
	void removeFromLavaList(Boss1LavaAttack *elementToRemove);
	void addAttack(Boss1LavaAttack* attackToAdd);
};