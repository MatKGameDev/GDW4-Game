#include "MainMenu.h"
#include "Tutorial.h"
#include "ControlsMenu.h"
#include "Boss1Scene.h"

Scene * MainMenu::createScene()
{
	Scene* scene = MainMenu::create();
	return scene;
}

bool MainMenu::init()
{
	if (!Scene::init())
		return false;

	currentSelection = MenuOptions::nothing;

	director = Director::getInstance();
	//Setting the default animation rate for the director
	director->setAnimationInterval(1.0f / 60.0f);
	director->setDisplayStats(1); //Remove this after debugging

	initUI();
	initAnimations();

	//init listeners
	initMouseListener();
	initControllerListener();

	scheduleUpdate();

	return true;
}

void MainMenu::initUI()
{
	//set our sprite labels

	Logo = Sprite::create("Backgrounds/Echoes_logo.png");
	Logo->setPosition(Vec2(950, 900));
	this->addChild(Logo, 10);

	startText = Sprite::create("Text/start.png");
	startText->setPosition(1920 / 2, 700);
	this->addChild(startText, 10);

	controlsText = Sprite::create("Text/controlsTest.png");
	controlsText->setPosition(1920 / 2, 500);
	this->addChild(controlsText, 10);

	exitText = Sprite::create("Text/exitTest.png");
	exitText->setPosition(1920 / 2, 300);
	this->addChild(exitText, 10);

	//set rects for label hover/click
	startRect.setRect(startText->getPositionX() - 300, startText->getPositionY() - 100, 600, 200);
	controlsRect.setRect(controlsText->getPositionX() - 300, controlsText->getPositionY() - 100, 600, 200);
	exitRect.setRect(exitText->getPositionX() - 300, exitText->getPositionY() - 100, 600, 200);

}

void MainMenu::initAnimations()
{
	auto sprite = cocos2d::Sprite::create("Backgrounds/greyBackground.png");
	auto anim = cocos2d::AnimationCache::getInstance()->getAnimation("main_menu_animation_key");
	auto action = cocos2d::Animate::create(anim);
	sprite->stopAllActions();
	sprite->runAction(cocos2d::RepeatForever::create(action->clone()));
	sprite->setAnchorPoint(Vec2(0, 0));
	sprite->setPosition(0, 0);
	this->addChild(sprite, -5);
}

void MainMenu::initMouseListener()
{
	//Init the mouse listener
	mouseListener = EventListenerMouse::create();

	//On Mouse Down
	mouseListener->onMouseDown = CC_CALLBACK_1(MainMenu::mouseDownCallback, this);

	//On Mouse Up
	mouseListener->onMouseUp = CC_CALLBACK_1(MainMenu::mouseUpCallback, this);

	//On Mouse Move
	mouseListener->onMouseMove = CC_CALLBACK_1(MainMenu::mouseMoveCallback, this);

	//On Mouse Scroll
	mouseListener->onMouseScroll = CC_CALLBACK_1(MainMenu::mouseScrollCallback, this);

	//Add the mouse listener to the dispatcher
	_eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);
}

void MainMenu::initControllerListener()
{
	controllerListener = EventListenerController::create();

	//set up callbacks
	controllerListener->onKeyDown = CC_CALLBACK_3(MainMenu::buttonPressCallback, this);
	controllerListener->onKeyUp = CC_CALLBACK_3(MainMenu::buttonReleaseCallback, this);
	controllerListener->onAxisEvent = CC_CALLBACK_3(MainMenu::axisEventCallback, this);

	controllerListener->onConnected = [](cocos2d::Controller* controller, cocos2d::Event* evt) {};

	//add the controller listener to the dispatcher
	_eventDispatcher->addEventListenerWithSceneGraphPriority(controllerListener, this);
}

//move to the next selection on the menu
void MainMenu::moveToNextMenuItem()
{
	switch (currentSelection)
	{
	case MenuOptions::nothing:
		currentSelection = MenuOptions::start;
		break;

	case MenuOptions::start:
		currentSelection = MenuOptions::controls;
		break;

	case MenuOptions::controls:
		currentSelection = MenuOptions::exit;
		break;

	case MenuOptions::exit:
		currentSelection = MenuOptions::start;
		break;
	}
}

//move back one selection on the menu
void MainMenu::moveToPreviousMenuItem()
{
	switch (currentSelection)
	{
	case MenuOptions::nothing:
		currentSelection = MenuOptions::start;
		break;

	case MenuOptions::start:
		currentSelection = MenuOptions::exit;
		break;

	case MenuOptions::controls:
		currentSelection = MenuOptions::start;
		break;

	case MenuOptions::exit:
		currentSelection = MenuOptions::controls;
		break;
	}
}

void MainMenu::update(float dt)
{
	if (!isTransitioning)
	{
		//check for mouse hover over menu items
		if (startRect.containsPoint(cursorPos) || currentSelection == MenuOptions::start)
			startText->setScale(1.2f);
		else
			startText->setScale(1.0f);

		if (controlsRect.containsPoint(cursorPos) || currentSelection == MenuOptions::controls)
			controlsText->setScale(1.2f);
		else
			controlsText->setScale(1.0f);

		if (exitRect.containsPoint(cursorPos) || currentSelection == MenuOptions::exit)
			exitText->setScale(1.2f);
		else
			exitText->setScale(1.0f);
	}
}

//performs duties to transition to the next scene
void MainMenu::transitionScene()
{
	this->removeAllChildrenWithCleanup(true);
	director->replaceScene(TransitionFade::create(1.f, Tutorial::createScene(), Color3B(0, 0, 0)));
	isTransitioning = true;
}


//--- Callbacks ---//

void MainMenu::mouseDownCallback(Event* event)
{
	//Cast the event as a mouse event
	EventMouse* mouseEvent = dynamic_cast<EventMouse*>(event);
	auto mouseButton = mouseEvent->getMouseButton();

	//Get the position of the mouse button press
	auto mouseClickPosition = mouseEvent->getLocationInView();

	if (mouseButton == cocos2d::EventMouse::MouseButton::BUTTON_LEFT)
	{
		//start game
		if (startRect.containsPoint(cursorPos))
		{
			transitionScene();
		}
		//open controls menu
		else if (controlsRect.containsPoint(cursorPos))
		{
			director->pushScene(ControlsMenu::createScene());
		}
		//exit game
		else if (exitRect.containsPoint(cursorPos))
		{
			director->end();
		}
	}
	if (mouseButton == cocos2d::EventMouse::MouseButton::BUTTON_RIGHT)
	{

	}
}

void MainMenu::mouseUpCallback(Event* event)
{
}

void MainMenu::mouseMoveCallback(Event* event)
{
	EventMouse* mouseEvent = dynamic_cast<EventMouse*>(event);
	cursorPos = mouseEvent->getLocationInView();
	cursorPos.y += 1080;
}

void MainMenu::mouseScrollCallback(Event* event)
{
}

void MainMenu::buttonPressCallback(Controller * controller, int keyCode, Event * event)
{
	switch (keyCode)
	{
	case ControllerInput::A:
		//start game
		if (currentSelection == MenuOptions::start)
		{
			transitionScene();
		}
		//open controls menu
		else if (currentSelection == MenuOptions::controls)
		{
			director->pushScene(ControlsMenu::createScene());
		}
		//exit game
		else if (currentSelection == MenuOptions::exit)
		{
			director->end();
		}
		break;

	case ControllerInput::Start:
		transitionScene();
		break;
	}
}

void MainMenu::buttonReleaseCallback(Controller * controller, int keyCode, Event * event)
{
}

void MainMenu::axisEventCallback(Controller * controller, int keyCode, Event * event)
{
	switch (keyCode)
	{
	//y axis of the left stick
	case ControllerInput::leftStickY:
		if (controller->getKeyStatus(keyCode).value >= 1 && ControllerInput::isLeftStickReset)
		{
			moveToPreviousMenuItem();
			ControllerInput::isLeftStickReset = false;
		}
		else if (controller->getKeyStatus(keyCode).value <= -1 && ControllerInput::isLeftStickReset)
		{
			moveToNextMenuItem();
			ControllerInput::isLeftStickReset = false;
		}
		else if (controller->getKeyStatus(keyCode).value > -0.9 && controller->getKeyStatus(keyCode).value < 0.9)
			ControllerInput::isLeftStickReset = true;
		break;
	}
}
