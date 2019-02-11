#include "Gameplay.h"

cocos2d::Scene* Gameplay::createScene()
{
	Scene* scene = Gameplay::create();
	return scene;
}

bool Gameplay::init()
{
	if (!Scene::init())
		return false;

	srand(time(NULL)); //seed rng
	director = Director::getInstance();
	//Setting the default animation rate for the director
	director->setAnimationInterval(1.0/60);
	director->setDisplayStats(1); //Remove this after debugging
	
	initGameObjects();
	initSprites();
	initListeners();

	scheduleUpdate();

	return true;
}

//initializes the user interface
void Gameplay::initUI()
{

}

void Gameplay::initGameObjects()
{
	Hero::hero->createHero(); //create hero (calls private constructor)
	Grapple::grapple->initGrapple(); //create grapple (calls private constructor)
}

void Gameplay::initSprites()
{
	//add background
	background = Sprite::create("Backgrounds/background.png");
	background->setAnchorPoint(Vec2(0.0f, 0.0f));
	this->addChild(background, 1);

	//add hero (singleton class)
	
	this->addChild(Hero::hero->sprite, 20);
	runAction(Follow::create(Hero::hero->sprite)); //set camera to follow main character

	Hero::hero->moveRight();

	//add grapple (singleton class)
	this->addChild(Grapple::grapple, 17);

	//add platforms for testing
	platform = new Platform(Vect2(180, 60));
	this->addChild(platform->sprite, 10);

	platform = new Platform(Vect2(330, 100));
	this->addChild(platform->sprite, 10);

	platform = new Platform(Vect2(500, 400));
	this->addChild(platform->sprite, 10);

	platform = new Platform(Vect2(900, 450));
	this->addChild(platform->sprite, 10);

	platform = new Platform(Vect2(1100, 500));
	this->addChild(platform->sprite, 10);
}

void Gameplay::initListeners()
{
	//Init the mouse listener
	initMouseListener();

	//Init the keyboard listener
	initKeyboardListener();
}

void Gameplay::initMouseListener()
{
	//Init the mouse listener
	mouseListener = EventListenerMouse::create();

	//On Mouse Down
	mouseListener->onMouseDown = CC_CALLBACK_1(Gameplay::mouseDownCallback, this);

	//On Mouse Up
	mouseListener->onMouseUp = CC_CALLBACK_1(Gameplay::mouseUpCallback, this);

	//On Mouse Move
	mouseListener->onMouseMove = CC_CALLBACK_1(Gameplay::mouseMoveCallback, this);

	//On Mouse Scroll
	mouseListener->onMouseScroll = CC_CALLBACK_1(Gameplay::mouseScrollCallback, this);

	//Add the mouse listener to the dispatcher
	_eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);
}

void Gameplay::initKeyboardListener()
{
	//Create the keyboard listener
	keyboardListener = EventListenerKeyboard::create();

	//Setting up callbacks
	keyboardListener->onKeyPressed = CC_CALLBACK_2(Gameplay::keyDownCallback, this);
	keyboardListener->onKeyReleased = CC_CALLBACK_2(Gameplay::keyUpCallback, this);

	//Add the keyboard listener to the dispatcher
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);
}

//UPDATE
void Gameplay::update(float dt)
{
	Hero::hero->update(dt); //update our hero
	//if (hero->invincibilityTimer > 0)
	//	flickerSprite(); //flicker sprite if it's invincible

	spawnEnemies();     //spawn enemies if needed 
	updateObjects(dt);  //update objects
	updateEnemies(dt);  //update enemies
}

void Gameplay::spawnEnemies()
{
	//spawns all enemies to keep a certain amount of each in the map

}

void Gameplay::updateObjects(float dt)
{
	//update all platforms
	for (int i = 0; i < Platform::platformList.size(); i++)
		Platform::platformList[i]->update();

	//update grapple
	Grapple::grapple->update(dt, this);
}

void Gameplay::updateEnemies(float dt)
{
	
}

//removes all game objects from the world
void Gameplay::removeAllObjects()
{
	
}

//flickers sprite every 1/10th of a second (typically to display invincibility)
void Gameplay::flickerSprite()
{
	//if (((int)(ship->invincibilityTimer * 10)) % 2 == 1)
	//	ship->sprite->setZOrder(0); //flicker the ship (hide it behind background)
	//else
	//	ship->sprite->setZOrder(10); //show the ship again
}

//--- Callbacks ---//

void Gameplay::mouseDownCallback(Event* event)
{
	//Cast the event as a mouse event
	EventMouse* mouseEvent = dynamic_cast<EventMouse*>(event);
	auto mouseButton = mouseEvent->getMouseButton();

	if (mouseButton == cocos2d::EventMouse::MouseButton::BUTTON_RIGHT)
	{
		//Get the position of the mouse button press
		auto mouseClickPosition = mouseEvent->getLocationInView();
		mouseClickPosition.y += 1080;

		auto mouseGameViewPosition = mouseClickPosition;
		//do some simple math to convert mouse click position on screen to in-game world position
		mouseGameViewPosition -= Vec2(1920 / 2, 1080 / 2); //update if screen size changes
		mouseGameViewPosition += Hero::hero->sprite->getPosition();

		Grapple::grapple->shoot(Vect2(mouseGameViewPosition)); //shoot the grapple
	}
}

void Gameplay::mouseUpCallback(Event* event)
{
}

void Gameplay::mouseMoveCallback(Event* event)
{
}

void Gameplay::mouseScrollCallback(Event* event)
{
}

void Gameplay::keyDownCallback(EventKeyboard::KeyCode keyCode, Event* event)
{
	//WASD controls
	if (keyCode == EventKeyboard::KeyCode::KEY_A)
		Hero::hero->moveState = Hero::MoveDirection::movingLeft;
	else if (keyCode == EventKeyboard::KeyCode::KEY_D)
		Hero::hero->moveState = Hero::MoveDirection::movingRight;
	else if (keyCode == EventKeyboard::KeyCode::KEY_S)
	{
		//if hero is at the end of a grapple, hitting S allows them to remove the delay and immediately start falling
		if (Grapple::grapple->isHeroAtEndPoint)
			Grapple::grapple->unLatch();
	}

	if (keyCode == EventKeyboard::KeyCode::KEY_SPACE)
	{
		if (Grapple::grapple->isHeroAtEndPoint)
		{
			Grapple::grapple->unLatch();
			Hero::hero->velocity.y += Hero::hero->JUMP_VELOCITY / 4; //add extra jump height on a grapple jump
		}

		Hero::hero->jump();
	}

	if (keyCode == EventKeyboard::KeyCode::KEY_ESCAPE)
	{

	}
}

void Gameplay::keyUpCallback(EventKeyboard::KeyCode keyCode, Event* event)
{
	if (keyCode == EventKeyboard::KeyCode::KEY_A && Hero::hero->moveState == Hero::MoveDirection::movingLeft)
		Hero::hero->moveState = Hero::MoveDirection::idle;
	else if (keyCode == EventKeyboard::KeyCode::KEY_D && Hero::hero->moveState == Hero::MoveDirection::movingRight)
		Hero::hero->moveState = Hero::MoveDirection::idle;
}