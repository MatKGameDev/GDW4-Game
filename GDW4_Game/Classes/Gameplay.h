#pragma once
#ifndef GAMEPLAY_H
#define GAMEPLAY_H

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

class Boss; //forward declare
class MouseAndKeyboardHandler;
class ControllerHandler;

class Gameplay : public cocos2d::Scene
{
public:
	CREATE_FUNC(Gameplay);
	static Scene* createScene();

	Boss* boss;

	bool isTransitioning;

	virtual bool init();
	void initUI();
	void initGameObjects();
	void initSprites();
	void initListeners();

	void update(float dt) override;
	void spawnEnemies();
	
	void removeAllObjects();


	//controller callbacks
	void buttonPressCallback(Controller* controller, int keyCode, Event* event);
	void buttonReleaseCallback(Controller* controller, int keyCode, Event* event);
	void axisEventCallback(Controller* controller, int keyCode, Event* event);

private:
	Director* director;

	EventListenerMouse* mouseListener;
	EventListenerKeyboard* keyboardListener;
	EventListenerController* controllerListener;

	MouseAndKeyboardHandler* mouseAndKeyboardHandler;
	ControllerHandler* controllerHandler;

	Vect2 mousePosition;

	Sprite* background;

	DrawNode* testHurtbox; //for testing hurtbox
	DrawNode* testMeleeAttack; //for testing melee attack

	//Utility functions
	void updateObjects(const float& dt);
	void updateEnemies(const float& dt);
};
#endif