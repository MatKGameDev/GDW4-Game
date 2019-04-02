#include "Boss1Scene.h"
#include "PauseMenu.h"
#include <iostream>
#include "HeroStateManager.h"
#include "Boss/General/Boss.h"
#include "XinputManager.h"
#include "DeathScreen.h"
#include "VictoryScreen.h"
#include "Boss/Attacks/Projectiles.h"

cocos2d::Scene* Boss1Scene::createScene()
{
	Scene* scene = Boss1Scene::create();
	return scene;
}

bool Boss1Scene::init()
{
	if (!Scene::init())
		return false;

	isTransitioning = false;

	srand(time(NULL)); //seed rng
	director = Director::getInstance();
	//Setting the default animation rate for the director
	director->setAnimationInterval(1.0f / 60.0f);
	director->setDisplayStats(1); //Remove this after debugging

	initGameObjects();
	initSprites();
	initListeners();

	scheduleUpdate();

	return true;
}

//initializes the user interface
void Boss1Scene::initUI()
{

}

void Boss1Scene::initGameObjects()
{
	Hero::hero->moveState = Hero::MoveDirection::idle;

	GameObject::MAX_X = 1856.0f;
	GameObject::MAX_Y = 952.0f;

	boss = new Boss(Hero::hero, this);
}

void Boss1Scene::initSprites()
{
	//add background
	background = Sprite::create("Backgrounds/bossBackground.png");
	background->setAnchorPoint(Vec2(0.0f, 0.0f));
	this->addChild(background, 1);

	//delete any existing tiles before we import our map
	TileBase::deleteAllTiles();
	//get the tilemap in
	cocos2d::TMXTiledMap* testTileMap = TMXTiledMap::create("Tilemaps/bossMap.tmx"); //ayy it works
	addChild(testTileMap, 1);

	cocos2d::TMXLayer* groundLayer = testTileMap->getLayer("tiles");
	cocos2d::TMXLayer* platformLayer = testTileMap->getLayer("platforms");
	cocos2d::TMXLayer* pillarLayer = testTileMap->getLayer("pillars");

	unsigned int tileMapWidth = testTileMap->getMapSize().width;   //map width
	unsigned int tileMapHeight = testTileMap->getMapSize().height; //map height
	for (unsigned int x = 0; x < tileMapWidth; x++)       //width of map grid
	{
		for (unsigned int y = 0; y < tileMapHeight; y++)  //height of map grid
		{
			cocos2d::Sprite* currentTile = groundLayer->getTileAt(Vec2(x, y));
			if (currentTile != NULL)
			{
				GroundTile* newGroundTile = new GroundTile(currentTile->getPosition(), 64);

				//set collision flags if there are adjacent ground tiles
				//we have to do our own x and y validation because cocos sucks and crashes otherwise
				if (x != 0)
				{
					if (groundLayer->getTileAt(Vec2(x - 1, y)) != NULL)
						newGroundTile->ignoreLeftCollision = true;
				}
				if (x != tileMapWidth - 1)
				{
					if (groundLayer->getTileAt(Vec2(x + 1, y)) != NULL)
						newGroundTile->ignoreRightCollision = true;
				}
				if (y != 0)
				{
					if (groundLayer->getTileAt(Vec2(x, y - 1)) != NULL)
						newGroundTile->ignoreTopCollision = true;
				}
				if (y != tileMapHeight - 1)
				{
					if (groundLayer->getTileAt(Vec2(x, y + 1)) != NULL)
						newGroundTile->ignoreBottomCollision = true;
				}
			}

			currentTile = platformLayer->getTileAt(Vec2(x, y));
			if (currentTile != NULL)
			{
				PlatformTile* newPlatformTile = new PlatformTile(currentTile->getPosition(), 64);
			}
		}
	}

	//add hero (singleton class)
	Hero::hero->sprite = Sprite::create("Sprites/shooting_test.png");
	this->addChild(Hero::hero->sprite, 20);
	Hero::hero->sprite->setPosition(Vec2(700, 200));
	Hero::hero->lookState = Hero::LookDirection::lookingLeft; //make sure they're looking towards the boss
	HeroStateManager::idle->onEnter();

	Hero::hero->arm = cocos2d::Sprite::create("Sprites/armV2.png");
	Hero::hero->arm->setVisible(0); //make arm invisible to begin with
	Hero::hero->arm->setAnchorPoint(Vec2(0.5f, 0.0f));
	this->addChild(Hero::hero->arm, 21); //add hero arm

	//add boss
	this->addChild(boss->getSprite(), 17);

	//add hero hurtbox FOR TESTING PURPOSES
	testHurtbox = DrawNode::create();
	this->addChild(testHurtbox, 30);
	//add fire melee attack hixbox FOR TESTING PURPOSES
	testMeleeAttack = DrawNode::create();
	this->addChild(testMeleeAttack, 40);

	//add grapple sprite
	//add repeating pattern to grapple sprite
	Grapple::grapple->sprite = Sprite::create("Sprites/grapple.png");
	Texture2D::TexParams params;
	params.minFilter = GL_NEAREST;
	params.magFilter = GL_NEAREST;
	params.wrapS = GL_REPEAT;
	params.wrapT = GL_REPEAT;
	Grapple::grapple->sprite->getTexture()->setTexParameters(params);
	Grapple::grapple->sprite->setVisible(0);
	Grapple::grapple->sprite->setAnchorPoint(Vec2(0.5, 0));
	this->addChild(Grapple::grapple->sprite, 5);

	//grapple tip
	Grapple::grapple->tip = Sprite::create("Sprites/grappleTip.png");
	//Grapple::grapple->tip->setAnchorPoint(Vec2(0.5, 0));
	this->addChild(Grapple::grapple->tip, 7);

	//grapple destination indicator
	Grapple::grapple->indicator = Sprite::create("Sprites/grappleIndicator.png");
	Grapple::grapple->indicator->setVisible(0);
	this->addChild(Grapple::grapple->indicator, 6);
}

void Boss1Scene::initListeners()
{
	//Init the mouse listener
	initMouseListener();
	//Init the keyboard listener
	initKeyboardListener();
	//init controller listener
	initControllerListener();
}

void Boss1Scene::initMouseListener()
{
	//Init the mouse listener
	mouseListener = EventListenerMouse::create();

	//On Mouse Down
	mouseListener->onMouseDown = CC_CALLBACK_1(Boss1Scene::mouseDownCallback, this);

	//On Mouse Up
	mouseListener->onMouseUp = CC_CALLBACK_1(Boss1Scene::mouseUpCallback, this);

	//On Mouse Move
	mouseListener->onMouseMove = CC_CALLBACK_1(Boss1Scene::mouseMoveCallback, this);

	//On Mouse Scroll
	mouseListener->onMouseScroll = CC_CALLBACK_1(Boss1Scene::mouseScrollCallback, this);

	//Add the mouse listener to the dispatcher
	_eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);
}

void Boss1Scene::initKeyboardListener()
{
	//Create the keyboard listener
	keyboardListener = EventListenerKeyboard::create();

	//Setting up callbacks
	keyboardListener->onKeyPressed = CC_CALLBACK_2(Boss1Scene::keyDownCallback, this);
	keyboardListener->onKeyReleased = CC_CALLBACK_2(Boss1Scene::keyUpCallback, this);

	//Add the keyboard listener to the dispatcher
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);
}

void Boss1Scene::initControllerListener()
{
	controllerListener = EventListenerController::create();

	//set up callbacks
	controllerListener->onKeyDown = CC_CALLBACK_3(Boss1Scene::buttonPressCallback, this);
	controllerListener->onKeyUp = CC_CALLBACK_3(Boss1Scene::buttonReleaseCallback, this);
	controllerListener->onAxisEvent = CC_CALLBACK_3(Boss1Scene::axisEventCallback, this);

	controllerListener->onConnected = [](cocos2d::Controller* controller, cocos2d::Event* evt) {};

	//add the controller listener to the dispatcher
	_eventDispatcher->addEventListenerWithSceneGraphPriority(controllerListener, this);
}

//UPDATE
void Boss1Scene::update(float dt)
{
	if (!isTransitioning)
	{
		Grapple::grapple->update(dt, this); //update grapple
		Hero::hero->update(dt); //update our hero

		testHurtbox->clear();
		//DRAW HURTBOX FOR TESTING
		testHurtbox->drawSolidRect(Vec2(Hero::hero->hurtBox.origin),
			Vec2(Hero::hero->hurtBox.origin.x + Hero::hero->hurtBox.size.width,
				Hero::hero->hurtBox.origin.y + Hero::hero->hurtBox.size.height),
			Color4F(1.0f, 0.0f, 0.0f, 0.f));
		//DRAW MOVEBOX FOR TESTING
		testHurtbox->drawSolidRect(Vec2(Hero::hero->moveBox.origin.x, Hero::hero->moveBox.origin.y),
			Vec2(Hero::hero->moveBox.origin.x + Hero::hero->moveBox.size.width,
				Hero::hero->moveBox.origin.y + Hero::hero->moveBox.size.height),
			Color4F(0.0f, 1.0f, 0.0f, .0f));
		//DRAW BOSS HITBOX FOR TESTING


		testMeleeAttack->clear();
		//DRAW MELEE ATTACK HITBOX FOR TESTING
		testMeleeAttack->drawSolidRect(HeroAttackManager::currentAttack->hitbox.origin,
			Vec2(HeroAttackManager::currentAttack->hitbox.getMaxX(), HeroAttackManager::currentAttack->hitbox.getMaxY()),
			Color4F(1.0f, 0.7f, 0.8f, 0.3f));

		spawnEnemies();     //spawn enemies if needed 
		updateObjects(dt);  //update objects
		updateEnemies(dt);  //update enemies

		//FOR TESTING BOSS DEATH
		if (boss->getHealth() == 0)
		{
			Hero::hero->reset(); //reset hero
			TileBase::deleteAllTiles();
			director->replaceScene(TransitionFade::create(2.0f, VictoryScreen::createScene(), Color3B(0, 0, 0)));
			isTransitioning = true;
		}
		else if (Hero::hero->health == 0)
		{
			Hero::hero->reset(); //reset hero
			TileBase::deleteAllTiles();
			director->replaceScene(TransitionFade::create(2.0f, DeathScreen::createScene(), Color3B(0, 0, 0)));
			isTransitioning = true;
		}
	}
}

void Boss1Scene::spawnEnemies()
{
	//spawns all enemies to keep a certain amount of each in the map

}

void Boss1Scene::updateObjects(float dt)
{
	//update all platforms
	unsigned int numPlatforms = Platform::platformList.size();
	for (unsigned int i = 0; i < numPlatforms; i++)
		Platform::platformList[i]->update();

	//update all ice projectiles
	for (unsigned int i = 0; i < IceProjectile::iceProjectileList.size(); i++)
		IceProjectile::iceProjectileList[i]->update(dt);
}

void Boss1Scene::updateEnemies(float dt)
{
	//update boss
	boss->update(dt);

	//check for an attack hitting the boss
	HeroAttackBase* currentAttack = HeroAttackManager::currentAttack;
	for (auto i : boss->getHitBox())
	{
		if (currentAttack == HeroAttackManager::meleeFire && myHelper::isCollision(currentAttack->hitbox,i->hitBox))
		{
			currentAttack->disabled = true;
			boss->takeDamage();
		}

		//check for collision on boss
		if (Hero::hero->isHitboxCollision(i->hitBox))
		{
			Hero::hero->takeDamage(i->hitBox.getMidX());
		}
	}

	//loop through each attack checking for collisions

	for (auto i : boss->getLavaList())
	{
		if (Hero::hero->isHitboxCollision(i->getHitBox()))
		{
			if (i->getAttackType() == Boss1LavaAttack::BossAttack::Flamethrower)
				Hero::hero->takeDamage(i->getHitBox().getMinX());
			else //not flamethrower attack
				Hero::hero->takeDamage(i->getHitBox().getMidX());

			i->hitByHero();
		}
	}
}

//removes all game objects from the world
void Boss1Scene::removeAllObjects()
{

}

//--- Callbacks ---//

void Boss1Scene::mouseDownCallback(Event* event)
{
	//Cast the event as a mouse event
	EventMouse* mouseEvent = dynamic_cast<EventMouse*>(event);
	auto mouseButton = mouseEvent->getMouseButton();

	if (mouseButton == cocos2d::EventMouse::MouseButton::BUTTON_LEFT)
	{
		HeroAttackManager::setCurrentAttack(HeroAttackTypes::meleeFireA, nullptr); //can pass a nullptr because we dont need to add anything to the scene for melee attacks
	}
	if (mouseButton == cocos2d::EventMouse::MouseButton::BUTTON_RIGHT)
	{
		//Get the position of the mouse button press
		auto mouseClickPosition = mouseEvent->getLocationInView();
		mouseClickPosition.y += 1080;

		auto mouseGameViewPosition = mouseClickPosition;
		mouseGameViewPosition.y += 15;

		Grapple::grapple->shoot(Vect2(mouseGameViewPosition)); //shoot the grapple
	}
}

void Boss1Scene::mouseUpCallback(Event* event)
{
}

void Boss1Scene::mouseMoveCallback(Event* event)
{
}

void Boss1Scene::mouseScrollCallback(Event* event)
{
}

void Boss1Scene::keyDownCallback(EventKeyboard::KeyCode keyCode, Event* event)
{
	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_A:
		HeroStateManager::currentState->handleInput(InputType::p_a);
		Hero::hero->lookState = Hero::LookDirection::lookingLeft;
		Hero::hero->moveState = Hero::MoveDirection::movingLeft;
		break;

	case EventKeyboard::KeyCode::KEY_D:
		HeroStateManager::currentState->handleInput(InputType::p_d);
		Hero::hero->lookState = Hero::LookDirection::lookingRight;
		Hero::hero->moveState = Hero::MoveDirection::movingRight;
		break;

	case EventKeyboard::KeyCode::KEY_S:
		HeroStateManager::currentState->handleInput(InputType::p_s);
		//HeroAttackBase::isSKeyHeld = true;
		break;

	case EventKeyboard::KeyCode::KEY_W:
		HeroAttackBase::isWKeyHeld = true;
		break;

	case EventKeyboard::KeyCode::KEY_SPACE:
		HeroStateManager::currentState->handleInput(InputType::p_space);
		break;

		//ATTACKS FOR TESTING. TODO: remove later and set to proper keybinds (numbers to swap between attacks?)
	case EventKeyboard::KeyCode::KEY_Q:
		HeroAttackManager::setCurrentAttack(HeroAttackTypes::meleeFireA, nullptr); //scene can be nullptr since we dont actually add anything to the scene in melee attacks
		break;

	case EventKeyboard::KeyCode::KEY_E:
		//HeroAttackManager::setCurrentAttack(HeroAttackTypes::projectileIceA, this);
		break;

	case EventKeyboard::KeyCode::KEY_ESCAPE:
		director->pushScene(PauseMenu::createScene());
	}
}

void Boss1Scene::keyUpCallback(EventKeyboard::KeyCode keyCode, Event* event)
{
	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_A:
		//make sure the hero is moving in this direction before we decide if they are now idle
		if (Hero::hero->moveState == Hero::MoveDirection::movingLeft)
			Hero::hero->moveState = Hero::MoveDirection::idle;
		break;

	case EventKeyboard::KeyCode::KEY_D:
		//make sure the hero is moving in this direction before we decide if they are now idle
		if (Hero::hero->moveState == Hero::MoveDirection::movingRight)
			Hero::hero->moveState = Hero::MoveDirection::idle;
		break;

	case EventKeyboard::KeyCode::KEY_S:
		HeroAttackBase::isSKeyHeld = false;
		break;

	case EventKeyboard::KeyCode::KEY_W:
		HeroAttackBase::isWKeyHeld = false;
		break;

	case EventKeyboard::KeyCode::KEY_SPACE:
		HeroStateManager::currentState->handleInput(InputType::r_space);
		break;
	}
}

void Boss1Scene::buttonPressCallback(Controller * controller, int keyCode, Event * event)
{
	switch (keyCode)
	{
	case ControllerInput::A:
		HeroStateManager::currentState->handleInput(InputType::p_space);
		break;

	case ControllerInput::Start:
		director->pushScene(PauseMenu::createScene());
		break;
	}
}

void Boss1Scene::buttonReleaseCallback(Controller * controller, int keyCode, Event * event)
{
	switch (keyCode)
	{
	case ControllerInput::A:
		HeroStateManager::currentState->handleInput(InputType::r_space);
		break;
	}
}

void Boss1Scene::axisEventCallback(Controller * controller, int keyCode, Event * event)
{
	switch (keyCode)
	{
		//x axis of the left stick
	case ControllerInput::leftStickX:
		//moving to the left
		if (controller->getKeyStatus(keyCode).value <= -1)
		{
			ControllerInput::isLeftStickIdle = false;
			ControllerInput::isControllerUsed = true; //controller has been used this playthrough
			HeroStateManager::currentState->handleInput(InputType::p_a);
			Hero::hero->lookState = Hero::LookDirection::lookingLeft;
			Hero::hero->moveState = Hero::MoveDirection::movingLeft;
		}
		//moving to the right
		else if (controller->getKeyStatus(keyCode).value >= 1)
		{
			ControllerInput::isLeftStickIdle = false;
			ControllerInput::isControllerUsed = true; //controller has been used this playthrough
			HeroStateManager::currentState->handleInput(InputType::p_d);
			Hero::hero->lookState = Hero::LookDirection::lookingRight;
			Hero::hero->moveState = Hero::MoveDirection::movingRight;
		}
		else if (!ControllerInput::isLeftStickIdle) //not moving AND left stick isn't at rest
		{
			Hero::hero->moveState = Hero::MoveDirection::idle;
			ControllerInput::isLeftStickIdle = true;
		}
		break;

		//y axis of the left stick
	case ControllerInput::leftStickY:
		if (controller->getKeyStatus(keyCode).value >= 1)
			HeroAttackBase::isWKeyHeld = true;
		else
		{
			HeroAttackBase::isWKeyHeld = false;
			if (controller->getKeyStatus(keyCode).value <= -1)
				HeroStateManager::currentState->handleInput(InputType::p_s);
		}
		break;

	case ControllerInput::leftTrigger:
		//check for attack
		if (controller->getKeyStatus(keyCode).value >= 1 && ControllerInput::isLeftTriggerReset)
		{
			ControllerInput::isLeftTriggerReset = false;
			HeroAttackManager::setCurrentAttack(HeroAttackTypes::meleeFireA, nullptr); //can pass a nullptr because we dont need to add anything to the scene for melee attacks
		}
		else if (controller->getKeyStatus(keyCode).value <= -1)
			ControllerInput::isLeftTriggerReset = true;
		break;

	case ControllerInput::rightTrigger:
		if (controller->getKeyStatus(keyCode).value >= 1 && ControllerInput::isRightTriggerReset)
		{
			ControllerInput::isRightTriggerReset = false;

			//use xinput stuff to get a more accurate reading on the stick input than cocos' controller support
			XinputManager::instance->update();
			XinputController* controller1 = XinputManager::instance->getController(0);
			Stick sticks[2];
			controller1->getSticks(sticks);

			//calculate angle (in radians) using atan2 with the right stick's y and x values
			float grappleAngle = atan2(sticks[RS].x, sticks[RS].y);

			//check if right stick is at rest (account for reading being slightly off or controller rest not being perfectly calibrated)
			if (sticks[RS].x < 0.1 && sticks[RS].x > -0.1 && sticks[RS].y <= 0.1f && sticks[RS].y > -0.1f)
			{
				//calculate angle (in radians) using atan2 with the right stick's y and x values
				grappleAngle = atan2(0.0f, 0.0f);
			}
			Grapple::grapple->shoot(grappleAngle); //shoot grapple
		}
		else if (controller->getKeyStatus(keyCode).value <= -1)
			ControllerInput::isRightTriggerReset = true;
		break;
	}
}
