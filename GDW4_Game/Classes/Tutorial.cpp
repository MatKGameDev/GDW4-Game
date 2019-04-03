#include "Tutorial.h"
#include "Boss1Scene.h"
#include "PrettyPictureScene.h"
#include <iostream>
#include "HeroStateManager.h"
#include "PauseMenu.h"
#include "HelpBubble.h"
#include "ControllerInput.h"
#include "SpikeTile.h"
#include "DeathScreen.h"
#include "Hud.h"
#include <SimpleAudioEngine.h>

cocos2d::Scene* Tutorial::createScene()
{
	Scene* scene = Tutorial::create();
	return scene;
}

bool Tutorial::init()
{
	if (!Scene::init())
		return false;

	ControllerInput::isControllerUsed = false;
	isTransitioning = false;
	srand(time(NULL)); //seed rng
	director = Director::getInstance();
	//Setting the default animation rate for the director
	director->setAnimationInterval(1.0f / 60.0f);

	initUI();
	initGameObjects();
	initSprites();
	initListeners();
	initMusic();

	//Init music
	auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
	audio->playBackgroundMusic("wonderPlace.wav");

	
	scheduleUpdate();

	return true;
}

//initializes the user interface
void Tutorial::initUI()
{
	//initialize help bubbles
	HelpBubble* jumpHint = new HelpBubble("HintBubbles/jumpHint.png", cocos2d::Vec2(300, 300), 200, 500);
	jumpHint->sprite->setScale(1.2);
	this->addChild(jumpHint->sprite, 18);

	HelpBubble* holdJumpHint = new HelpBubble("HintBubbles/holdJumpHint.png", cocos2d::Vec2(2125, 450), 1950, 2300);
	holdJumpHint->sprite->setScale(1.2);
	this->addChild(holdJumpHint->sprite, 18);

	HelpBubble* grapplingHint = new HelpBubble("HintBubbles/grapplingHint.png", cocos2d::Vec2(3900, 375), 3690, 4050);
	grapplingHint->sprite->setScale(1.2);
	this->addChild(grapplingHint->sprite, 18);

	HelpBubble* attackHint = new HelpBubble("HintBubbles/attackHint.png", cocos2d::Vec2(4650, 740), 4400, 4800);
	attackHint->sprite->setScale(1.2);
	this->addChild(attackHint->sprite, 18);

	HelpBubble* dropHint = new HelpBubble("HintBubbles/dropHint.png", cocos2d::Vec2(5975, 875), 5600, 6200);
	dropHint->sprite->setScale(1.2);
	this->addChild(dropHint->sprite, 18);
}

void Tutorial::initGameObjects()
{
	//set bounds for the scene
	GameObject::MAX_X = 15000.0f;
	GameObject::MAX_Y = 1080.0f;
}

void Tutorial::initSprites()
{
	Vec2 origin = Director::sharedDirector()->getVisibleOrigin(); //origin point
	Size size = Director::sharedDirector()->getVisibleSize();  //screen size
	Vec2 center = Vec2(size.width / 2 + origin.x, size.height / 2 + origin.y); //center point

	fieldWidth = 13888;  //x boundary for camera
	fieldHeight = size.height - 40; //y boundary for camera

	Texture2D::TexParams params;
	params.minFilter = GL_NEAREST;
	params.magFilter = GL_NEAREST;
	params.wrapS = GL_REPEAT;
	params.wrapT = GL_REPEAT;

	//add background layers
	backgroundL1 = Sprite::create("Backgrounds/tutBackground_L1.png");
	backgroundL1->setAnchorPoint(Vec2(0.0f, 0.0f));
	backgroundL1->getTexture()->setTexParameters(params);
	backgroundL1->setTextureRect(cocos2d::Rect(0, 0, fieldWidth, fieldHeight));

	backgroundL2 = Sprite::create("Backgrounds/tutBackground_L2.png");
	backgroundL2->setAnchorPoint(Vec2(0.0f, 0.0f));
	backgroundL2->getTexture()->setTexParameters(params);
	backgroundL2->setTextureRect(cocos2d::Rect(0, 0, fieldWidth, fieldHeight));

	backgroundL3 = Sprite::create("Backgrounds/tutBackground_L3.png");
	backgroundL3->setAnchorPoint(Vec2(0.0f, 0.0f));
	backgroundL3->getTexture()->setTexParameters(params);
	backgroundL3->setTextureRect(cocos2d::Rect(0, 0, fieldWidth, fieldHeight));

	backgroundL4 = Sprite::create("Backgrounds/tutBackground_L4.png");
	backgroundL4->setAnchorPoint(Vec2(0.0f, 0.0f));
	backgroundL4->getTexture()->setTexParameters(params);
	backgroundL4->setTextureRect(cocos2d::Rect(0, 0, fieldWidth, fieldHeight));

	backgroundL5 = Sprite::create("Backgrounds/tutBackground_L5.png");
	backgroundL5->setAnchorPoint(Vec2(0.0f, 0.0f));
	backgroundL5->getTexture()->setTexParameters(params);
	backgroundL5->setTextureRect(cocos2d::Rect(0, 0, fieldWidth, fieldHeight));

	backgroundL6 = Sprite::create("Backgrounds/tutBackground_L6.png");
	backgroundL6->setAnchorPoint(Vec2(0.0f, 0.0f));
	backgroundL6->getTexture()->setTexParameters(params);
	backgroundL6->setTextureRect(cocos2d::Rect(0, 0, fieldWidth, fieldHeight));

	backgroundL7 = Sprite::create("Backgrounds/tutBackground_L7.png");
	backgroundL7->setAnchorPoint(Vec2(0.0f, 0.0f));
	backgroundL7->getTexture()->setTexParameters(params);
	backgroundL7->setTextureRect(cocos2d::Rect(0, 0, fieldWidth, fieldHeight));

	backgroundL8 = Sprite::create("Backgrounds/tutBackground_L8.png");
	backgroundL8->setAnchorPoint(Vec2(0.0f, 0.0f));
	backgroundL8->getTexture()->setTexParameters(params);
	backgroundL8->setTextureRect(cocos2d::Rect(0, 0, fieldWidth, fieldHeight));

	backgroundL9 = Sprite::create("Backgrounds/tutBackground_L9.png");
	backgroundL9->setAnchorPoint(Vec2(0.0f, 0.0f));
	backgroundL9->getTexture()->setTexParameters(params);
	backgroundL9->setTextureRect(cocos2d::Rect(0, 0, fieldWidth, fieldHeight));

	backgroundL10 = Sprite::create("Backgrounds/tutBackground_L10.png");
	backgroundL10->setAnchorPoint(Vec2(0.0f, 0.0f));
	backgroundL10->getTexture()->setTexParameters(params);
	backgroundL10->setTextureRect(cocos2d::Rect(0, 0, fieldWidth, fieldHeight));

	foregroundL1 = Sprite::create("Backgrounds/foreground1.png");
	foregroundL1->setAnchorPoint(Vec2(0.0f, 0.0f));
	foregroundL1->getTexture()->setTexParameters(params);
	foregroundL1->setTextureRect(cocos2d::Rect(0, -464, fieldWidth, 2048));

	foregroundL2 = Sprite::create("Backgrounds/foreground2.png");
	foregroundL2->setAnchorPoint(Vec2(0.0f, 0.0f));
	foregroundL2->getTexture()->setTexParameters(params);
	foregroundL2->setTextureRect(cocos2d::Rect(0, -464, fieldWidth, 2048));

	//create parallax node for background layers
	ParallaxNode* backGroundParallax = ParallaxNode::create();
	ParallaxNode* foregroundParallax = ParallaxNode::create();

	//add background layers to the parallax node with various scrolling speeds, push them all up a bit by using the offset
	backGroundParallax->addChild(backgroundL1, -20, Vec2(0.05, 0.05), Vec2(0, 100));
	backGroundParallax->addChild(backgroundL2, -19, Vec2(0.1, 0.1), Vec2(0, 100));
	backGroundParallax->addChild(backgroundL3, -18, Vec2(0.14, 0.14), Vec2(0, 100));
	backGroundParallax->addChild(backgroundL4, -17, Vec2(0.32, 0.32), Vec2(0, 100));
	backGroundParallax->addChild(backgroundL5, -16, Vec2(0.41, 0.41), Vec2(0, 100));
	backGroundParallax->addChild(backgroundL6, -15, Vec2(0.54, 0.54), Vec2(0, 100));
	backGroundParallax->addChild(backgroundL7, -14, Vec2(0.71, 0.71), Vec2(0, 100));
	backGroundParallax->addChild(backgroundL8, -13, Vec2(0.85, 0.85), Vec2(0, 100));
	backGroundParallax->addChild(backgroundL9, -12, Vec2(0.91, 0.91), Vec2(0, 100));
	backGroundParallax->addChild(backgroundL10, -12, Vec2(0.91, 0.91), Vec2(0, 100));


	foregroundParallax->addChild(foregroundL1, 91, Vec2(1.3, 1.3), Vec2(0, 00)); //foreground 1
	foregroundParallax->addChild(foregroundL2, 90, Vec2(1.1, 1.1), Vec2(0, 00)); //foreground 2



	this->addChild(backGroundParallax, -5);

	this->addChild(foregroundParallax, 90);


	//delete any existing tiles before we import our map
	TileBase::deleteAllTiles();
	//get the tilemap in
	cocos2d::TMXTiledMap* testTileMap = TMXTiledMap::create("Tilemaps/Final.tmx"); //ayy it works
	addChild(testTileMap, 1);

	cocos2d::TMXLayer* groundLayer = testTileMap->getLayer("Ground");
	cocos2d::TMXLayer* platformLayer = testTileMap->getLayer("platforms");
	cocos2d::TMXLayer* spikeLayer = testTileMap->getLayer("spikes");

	unsigned int tileMapWidth = testTileMap->getMapSize().width;   //map width
	unsigned int tileMapHeight = testTileMap->getMapSize().height; //map height
	for (unsigned int x = 0; x < tileMapWidth; x++)       //width of map grid
	{
		for (unsigned int y = 0; y < tileMapHeight; y++)  //height of map grid
		{
			//check for ground tile
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

			//check for platform tile
			currentTile = platformLayer->getTileAt(Vec2(x, y));
			if (currentTile != NULL)
				PlatformTile* newPlatformTile = new PlatformTile(currentTile->getPosition(), 64);

			//check for spike tile
			currentTile = spikeLayer->getTileAt(Vec2(x, y));
			if (currentTile != NULL)
				SpikeTile* newSpikeTile = new SpikeTile(currentTile->getPosition(), 64);
		}
	}

	//add hero (singleton class)
	Hero::hero->sprite = Sprite::create("Sprites/shooting_test.png");
	this->addChild(Hero::hero->sprite, 20);
	Hero::hero->sprite->setPosition(Vec2(20, 200));
	Hero::hero->lookState = Hero::LookDirection::lookingRight;
	Hero::hero->velocity.x = 0;
	HeroStateManager::idle->onEnter();

	//use a follow camera with strict dimensions for horizontal scrolling
	this->runAction(Follow::create(Hero::hero->sprite, Rect(0, 50, fieldWidth, fieldHeight)));

	Hero::hero->arm = cocos2d::Sprite::create("Sprites/armV2.png");
	Hero::hero->arm->setVisible(0); //make arm invisible to begin with
	Hero::hero->arm->setAnchorPoint(Vec2(0.5f, 0.0f));
	this->addChild(Hero::hero->arm, 21); //add hero arm

	//add grapple sprite
	//add repeating pattern to grapple sprite
	Grapple::grapple->sprite = Sprite::create("Sprites/grapple.png");
	Grapple::grapple->sprite->getTexture()->setTexParameters(params);
	Grapple::grapple->sprite->setVisible(0);
	Grapple::grapple->sprite->setAnchorPoint(Vec2(0.5, 0));
	this->addChild(Grapple::grapple->sprite, 5);

	//grapple tip sprite
	Grapple::grapple->tip = Sprite::create("Sprites/grappleTip.png");
	//Grapple::grapple->tip->setAnchorPoint(Vec2(0.5, 0));
	this->addChild(Grapple::grapple->tip, 7);

	//grapple destination indicator
	Grapple::grapple->indicator = Sprite::create("Sprites/grappleIndicator.png");
	Grapple::grapple->indicator->setVisible(0);
	this->addChild(Grapple::grapple->indicator, 6);
}

void Tutorial::initListeners()
{
	//Init the mouse listener
	initMouseListener();
	//Init the keyboard listener
	initKeyboardListener();
	//init controller listener
	initControllerListener();
}

void Tutorial::initMouseListener()
{
	//Init the mouse listener
	mouseListener = EventListenerMouse::create();

	//On Mouse Down
	mouseListener->onMouseDown = CC_CALLBACK_1(Tutorial::mouseDownCallback, this);

	//On Mouse Up
	mouseListener->onMouseUp = CC_CALLBACK_1(Tutorial::mouseUpCallback, this);

	//On Mouse Move
	mouseListener->onMouseMove = CC_CALLBACK_1(Tutorial::mouseMoveCallback, this);

	//On Mouse Scroll
	mouseListener->onMouseScroll = CC_CALLBACK_1(Tutorial::mouseScrollCallback, this);

	//Add the mouse listener to the dispatcher
	_eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);
}

void Tutorial::initKeyboardListener()
{
	//Create the keyboard listener
	keyboardListener = EventListenerKeyboard::create();

	//Setting up callbacks
	keyboardListener->onKeyPressed = CC_CALLBACK_2(Tutorial::keyDownCallback, this);
	keyboardListener->onKeyReleased = CC_CALLBACK_2(Tutorial::keyUpCallback, this);

	//add the keyboard listener to the dispatcher
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);
}

void Tutorial::initControllerListener()
{
	controllerListener = EventListenerController::create();

	//set up callbacks
	controllerListener->onKeyDown = CC_CALLBACK_3(Tutorial::buttonPressCallback, this);
	controllerListener->onKeyUp = CC_CALLBACK_3(Tutorial::buttonReleaseCallback, this);
	controllerListener->onAxisEvent = CC_CALLBACK_3(Tutorial::axisEventCallback, this);

	controllerListener->onConnected = [](cocos2d::Controller* controller, cocos2d::Event* evt) {};

	//add the controller listener to the dispatcher
	_eventDispatcher->addEventListenerWithSceneGraphPriority(controllerListener, this);
}

void Tutorial::initMusic()
{
	auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
	audio->resumeBackgroundMusic();
}

//UPDATE
void Tutorial::update(float dt)
{
	if (!isTransitioning)
	{
		Grapple::grapple->update(dt, this); //update grapple
		Hero::hero->update(dt); //update our hero

		spawnEnemies();     //spawn enemies if needed 
		updateObjects(dt);  //update objects
		updateEnemies(dt);  //update enemies

		//check if we should move to the next scene
		if (Hero::hero->moveBox.getMaxX() >= 13888)
		{
			Hero::hero->reset();
			Hero::hero->lookState = Hero::LookDirection::lookingRight; //make sure they're looking right (over the clif)
			HelpBubble::deleteAllInstances();
			director->replaceScene(TransitionFade::create(1.5f, PrettyPictureScene::createScene(), Color3B(0, 0, 0)));
			isTransitioning = true;
		}
		else if (Hero::hero->health == 0) //check for ded
		{
			Hero::hero->reset(); //reset hero
			HelpBubble::deleteAllInstances();
			director->replaceScene(TransitionFade::create(2.0f, DeathScreen::createScene(), Color3B(0, 0, 0)));
			isTransitioning = true;
		}
	}
	else //we are transitioning
	{
		//move hero down to the nearest block so they arent floating
		Hero::hero->velocity.y = -400;
		Hero::hero->updatePhysics(dt);

		unsigned int tileListSize = TileBase::tileList.size();
		for (unsigned int i = 0; i < tileListSize; i++)
		{
			if (TileBase::tileList[i]->checkAndResolveCollision(Hero::hero))
				HeroStateManager::idle->onEnter();
		}
	}
}

void Tutorial::spawnEnemies()
{
	//spawns all enemies to keep a certain amount of each in the map

}

void Tutorial::updateObjects(float dt)
{
	//update all platforms
	unsigned int numPlatforms = Platform::platformList.size();
	for (unsigned int i = 0; i < numPlatforms; i++)
		Platform::platformList[i]->update();

	//update all ice projectiles
	for (unsigned int i = 0; i < IceProjectile::iceProjectileList.size(); i++)
		IceProjectile::iceProjectileList[i]->update(dt);

	//update all help bubbles
	unsigned int numHelpBubbles = HelpBubble::helpBubbleList.size();
	for (unsigned int i = 0; i < numHelpBubbles; i++)
		HelpBubble::helpBubbleList[i]->update(dt);

	
	//update UI
	for (unsigned int i = 0; i < HudObject::HudList.size(); i++)
	{
		HudObject::HudList[i]->update(dt);
	}

}

void Tutorial::updateEnemies(float dt)
{

}

//removes all game objects from the world
void Tutorial::removeAllObjects()
{

}

//--- Callbacks ---//

void Tutorial::mouseDownCallback(Event* event)
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
		mouseGameViewPosition.y += 45;

		//calculate proper x position for grapple
		if (Hero::hero->getPosition().x > 1920/2)
		{
			//do some simple math to convert mouse click position on screen to in-game world position
			mouseGameViewPosition.x -= 1920 / 2; //update if screen size changes
			mouseGameViewPosition.x += Hero::hero->sprite->getPosition().x;
		}

		Grapple::grapple->shoot(Vect2(mouseGameViewPosition)); //shoot the grapple
	}
}

void Tutorial::mouseUpCallback(Event* event)
{
}

void Tutorial::mouseMoveCallback(Event* event)
{
}

void Tutorial::mouseScrollCallback(Event* event)
{
}

void Tutorial::keyDownCallback(EventKeyboard::KeyCode keyCode, Event* event)
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

	case EventKeyboard::KeyCode::KEY_W:
		HeroAttackBase::isWKeyHeld = true;
		break;

	case EventKeyboard::KeyCode::KEY_S:
		HeroStateManager::currentState->handleInput(InputType::p_s);
		//HeroAttackBase::isSKeyHeld = true;
		break;

	case EventKeyboard::KeyCode::KEY_SPACE:
		HeroStateManager::currentState->handleInput(InputType::p_space);
		break;

	case EventKeyboard::KeyCode::KEY_E:
		//HeroAttackManager::setCurrentAttack(HeroAttackTypes::projectileIceA, this);
		break;

	case EventKeyboard::KeyCode::KEY_ESCAPE:
		director->pushScene(PauseMenu::createScene());
	}
}

void Tutorial::keyUpCallback(EventKeyboard::KeyCode keyCode, Event* event)
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

	case EventKeyboard::KeyCode::KEY_W:
		HeroAttackBase::isWKeyHeld = false;
		break;

	case EventKeyboard::KeyCode::KEY_SPACE:
		HeroStateManager::currentState->handleInput(InputType::r_space);
		break;
	}
}

void Tutorial::buttonPressCallback(Controller * controller, int keyCode, Event * event)
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

void Tutorial::buttonReleaseCallback(Controller * controller, int keyCode, Event * event)
{
	switch (keyCode)
	{
	case ControllerInput::A:
		HeroStateManager::currentState->handleInput(InputType::r_space);
		break;
	}
}

void Tutorial::axisEventCallback(Controller * controller, int keyCode, Event * event)
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