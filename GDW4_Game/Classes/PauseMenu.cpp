#include "PauseMenu.h"
#include "Tutorial.h"
#include "Boss1Scene.h"
#include "ControlsMenu.h"

Scene * PauseMenu::createScene()
{
	Scene* scene = PauseMenu::create();
	return scene;
}

bool PauseMenu::init()
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

	auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
	
	audio->resumeBackgroundMusic();
	

	scheduleUpdate();

	return true;
}

void PauseMenu::initUI()
{
	//set our sprite labels
	background = Sprite::create("Backgrounds/pause_menu.png");
	background->setAnchorPoint(Vec2(0.0f, 0.0f));
	this->addChild(background, 5);

	resumeText = Sprite::create("Text/resumeTest.png");
	resumeText->setPosition(1920 / 2, 700);
	this->addChild(resumeText, 10);

	controlsText = Sprite::create("Text/controlsTest.png");
	controlsText->setPosition(1920 / 2, 500);
	this->addChild(controlsText, 10);

	exitText = Sprite::create("Text/exitTest.png");
	exitText->setPosition(1920 / 2, 300);
	this->addChild(exitText, 10);

	//set rects for label hover/click
	resumeRect.setRect(resumeText->getPositionX() - 300, resumeText->getPositionY() - 100, 600, 200);
	controlsRect.setRect(controlsText->getPositionX() - 300, controlsText->getPositionY() - 100, 600, 200);
	exitRect.setRect(exitText->getPositionX() - 300, exitText->getPositionY() - 100, 600, 200);
}

void PauseMenu::initAnimations()
{
}

void PauseMenu::initMouseListener()
{
	//Init the mouse listener
	mouseListener = EventListenerMouse::create();

	//On Mouse Down
	mouseListener->onMouseDown = CC_CALLBACK_1(PauseMenu::mouseDownCallback, this);

	//On Mouse Up
	mouseListener->onMouseUp = CC_CALLBACK_1(PauseMenu::mouseUpCallback, this);

	//On Mouse Move
	mouseListener->onMouseMove = CC_CALLBACK_1(PauseMenu::mouseMoveCallback, this);

	//On Mouse Scroll
	mouseListener->onMouseScroll = CC_CALLBACK_1(PauseMenu::mouseScrollCallback, this);

	//Add the mouse listener to the dispatcher
	_eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);
}

void PauseMenu::initControllerListener()
{
	controllerListener = EventListenerController::create();

	//set up callbacks
	controllerListener->onKeyDown = CC_CALLBACK_3(PauseMenu ::buttonPressCallback, this);
	controllerListener->onKeyUp = CC_CALLBACK_3(PauseMenu::buttonReleaseCallback, this);
	controllerListener->onAxisEvent = CC_CALLBACK_3(PauseMenu::axisEventCallback, this);

	controllerListener->onConnected = [](cocos2d::Controller* controller, cocos2d::Event* evt) {};

	//add the controller listener to the dispatcher
	_eventDispatcher->addEventListenerWithSceneGraphPriority(controllerListener, this);
}

//move to the next selection on the menu
void PauseMenu::moveToNextMenuItem()
{
	switch (currentSelection)
	{
	case MenuOptions::nothing:
		currentSelection = MenuOptions::resume;
		break;

	case MenuOptions::resume:
		currentSelection = MenuOptions::controls;
		break;

	case MenuOptions::controls:
		currentSelection = MenuOptions::exit;
		break;

	case MenuOptions::exit:
		currentSelection = MenuOptions::resume;
		break;
	}
}

//move back one selection on the menu
void PauseMenu::moveToPreviousMenuItem()
{
	switch (currentSelection)
	{
	case MenuOptions::nothing:
		currentSelection = MenuOptions::resume;
		break;

	case MenuOptions::resume:
		currentSelection = MenuOptions::exit;
		break;

	case MenuOptions::controls:
		currentSelection = MenuOptions::resume;
		break;

	case MenuOptions::exit:
		currentSelection = MenuOptions::controls;
		break;
	}
}

void PauseMenu::update(float dt)
{
	if (resumeRect.containsPoint(cursorPos) || currentSelection == MenuOptions::resume)
		resumeText->setScale(1.2f);
	else
		resumeText->setScale(1.0f);

	if (controlsRect.containsPoint(cursorPos) || currentSelection == MenuOptions::controls)
		controlsText->setScale(1.2f);
	else
		controlsText->setScale(1.0f);

	if (exitRect.containsPoint(cursorPos) || currentSelection == MenuOptions::exit)
		exitText->setScale(1.2f);
	else
		exitText->setScale(1.0f);
}


//--- Callbacks ---//

void PauseMenu::mouseDownCallback(Event* event)
{
	//Cast the event as a mouse event
	EventMouse* mouseEvent = dynamic_cast<EventMouse*>(event);
	auto mouseButton = mouseEvent->getMouseButton();

	//Get the position of the mouse button press
	auto mouseClickPosition = mouseEvent->getLocationInView();

	if (mouseButton == cocos2d::EventMouse::MouseButton::BUTTON_LEFT)
	{
		//resume game
		if (resumeRect.containsPoint(cursorPos))
		{
			director->popScene();
		}
		//bring up controls menu
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

void PauseMenu::mouseUpCallback(Event* event)
{
}

void PauseMenu::mouseMoveCallback(Event* event)
{
	EventMouse* mouseEvent = dynamic_cast<EventMouse*>(event);
	cursorPos = mouseEvent->getLocationInView();
	cursorPos.y += 1080;
}

void PauseMenu::mouseScrollCallback(Event* event)
{
}

void PauseMenu::buttonPressCallback(Controller * controller, int keyCode, Event * event)
{
	switch (keyCode)
	{
	case ControllerInput::A:
		//start game
		if (currentSelection == MenuOptions::resume)
		{
			director->popScene();
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

	case ControllerInput::B:
		director->popScene();
		break;

	case ControllerInput::Back:
		director->popScene();
		break;

	case ControllerInput::Start:
		director->popScene();
		break;
	}
}

void PauseMenu::buttonReleaseCallback(Controller * controller, int keyCode, Event * event)
{
}

void PauseMenu::axisEventCallback(Controller * controller, int keyCode, Event * event)
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
