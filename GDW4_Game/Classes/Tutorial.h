#pragma once
#ifndef TUTORIAL_H
#define TUTORIAL_H

#include "cocos2d.h"
#include "Vect2.h"
#include "Hero.h"
#include "Platform.h"
#include "Grapple.h"
#include "HeroAttackManager.h"
#include "IceProjectile.h"
#include "HeroMovementBase.h"
#include "PlatformTile.h"
#include "GroundTile.h"
#include "XinputManager.h"

class MouseAndKeyboardHandler;
class ControllerHandler;

using namespace cocos2d;

class Tutorial : public cocos2d::Scene
{
public:
	CREATE_FUNC(Tutorial);
	static Scene* createScene();

	bool isTransitioning;

	virtual bool init();
	void initUI();
	void initGameObjects();
	void initSprites();
	void initListeners();

	void update(float dt);
	void spawnEnemies();
	
	void removeAllObjects();
private:
	Director* director;

	EventListenerMouse* mouseListener;
	EventListenerKeyboard* keyboardListener;
	EventListenerController* controllerListener;

	MouseAndKeyboardHandler* mouseAndKeyboardHandler;
	ControllerHandler* controllerHandler;

	Vect2 mousePosition;

	float fieldWidth;
	float fieldHeight;

	Sprite* backgroundL1;
	Sprite* backgroundL2;
	Sprite* backgroundL3;
	Sprite* backgroundL4;
	Sprite* backgroundL5;
	Sprite* backgroundL6;
	Sprite* backgroundL7;
	Sprite* backgroundL8;
	Sprite* backgroundL9;
	Sprite* backgroundL10;

	Sprite* foregroundL1;
	Sprite* foregroundL2;

	DrawNode* testHurtbox; //for testing hurtbox
	DrawNode* testMeleeAttack; //for testing melee attack

	//Utility functions
	void updateObjects(const float& dt);
	void updateEnemies(const float& dt);
};
#endif