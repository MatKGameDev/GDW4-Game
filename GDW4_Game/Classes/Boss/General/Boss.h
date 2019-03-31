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
	enum HitboxIndex
	{
		idling, //Use this for idling, explosive bullet
		flameSplitter,
		flamethrower,
	};
	friend class FirstBossState;

	//Private data members
	int health;
	FirstBossState *state;
	cocos2d::Sprite *sprite;
	std::vector<Boss1LavaAttack*> lavaList;
	std::vector<std::vector<HitBox*>> hitBoxLists;
	HitboxIndex hitboxIndex{ idling };
	cocos2d::Scene *bossScene;

	//Private functions
	void initHitbox();
	std::vector<HitBox*> initIdleHitbox() const;
	std::vector<HitBox*> initFlameSplitHitbox() const;
	std::vector<HitBox*> initFlameThrowerHitbox() const;
public:
	Boss(Hero* heroInstance, cocos2d::Scene *sceneForBoss, float height = 581, float width = 325);
	~Boss();

	//Setters
	void setState(FirstBossState *newState);
	void setHitboxIndex(HitboxIndex newIndex);

	//Getters
	int getHealth() const;
	cocos2d::Sprite* getSprite() const;
	std::vector<Boss1LavaAttack*> getLavaList() const;
	cocos2d::Scene* getBossScene() const;
	std::vector<HitBox*> getHitBox() const;
	FirstBossState* getCurrentState() const;

	//Member functions
	void takeDamage();
	void update(const float &deltaT);
	
	//Attack functions
	void spewLava();
	void activateFlameThrower();
	void shootExplosiveBullet();

	//Utility functions
	void removeFromLavaList(Boss1LavaAttack *attackToRemove);
	void addAttack(Boss1LavaAttack* attackToAdd);
};