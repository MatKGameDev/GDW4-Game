#pragma once
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

using namespace cocos2d;

class Gameplay : public cocos2d::Scene
{
public:
	CREATE_FUNC(Gameplay);
	static Scene* createScene();

	virtual bool init();
	void initUI();
	void initGameObjects();
	void initSprites();
	void initListeners();
	void initMouseListener();
	void initKeyboardListener();

	void update(float dt);
	void spawnEnemies();
	void updateObjects(float dt);
	void updateEnemies(float dt);
	void removeAllObjects();

	void flickerSprite();

	//Callbacks
	void mouseDownCallback(Event* event);
	void mouseUpCallback(Event* event);
	void mouseMoveCallback(Event* event);
	void mouseScrollCallback(Event* event);
	void keyDownCallback(EventKeyboard::KeyCode keycode, Event* event);
	void keyUpCallback(EventKeyboard::KeyCode keycode, Event* event);

private:
	Director* director;

	EventListenerMouse* mouseListener;
	EventListenerKeyboard* keyboardListener;
	Vect2 mousePosition;

	Sprite* background;

	DrawNode* testHurtbox; //for testing hurtbox
	DrawNode* testMeleeAttack; //for testing melee attack
};