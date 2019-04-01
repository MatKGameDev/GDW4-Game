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
	void initMouseListener();
	void initKeyboardListener();
	void initControllerListener();

	void update(float dt);
	void spawnEnemies();
	void updateObjects(float dt);
	void updateEnemies(float dt);
	void removeAllObjects();

	//mouse callbacks
	void mouseDownCallback(Event* event);
	void mouseUpCallback(Event* event);
	void mouseMoveCallback(Event* event);
	void mouseScrollCallback(Event* event);

	//keyboard callbacks
	void keyDownCallback(EventKeyboard::KeyCode keycode, Event* event);
	void keyUpCallback(EventKeyboard::KeyCode keycode, Event* event);

	//controller callbacks
	void buttonPressCallback(Controller* controller, int keyCode, Event* event);
	void buttonReleaseCallback(Controller* controller, int keyCode, Event* event);
	void axisEventCallback(Controller* controller, int keyCode, Event* event);

private:
	Director* director;

	EventListenerMouse* mouseListener;
	EventListenerKeyboard* keyboardListener;
	EventListenerController* controllerListener;

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
};
#endif