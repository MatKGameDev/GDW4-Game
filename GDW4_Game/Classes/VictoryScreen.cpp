#include "VictoryScreen.h"
#include "MainMenu.h"
#include <SimpleAudioEngine.h>

Scene * VictoryScreen::createScene()
{
	Scene* scene = VictoryScreen::create();
	return scene;
}

bool VictoryScreen::init()
{
	if (!Scene::init())
		return false;

	currentSelection = MenuOptions::nothing;

	director = Director::getInstance();
	//Setting the default animation rate for the director
	director->setAnimationInterval(1.0f / 60.0f);

	initUI();
	initAnimations();

	//init listeners
	initMouseListener();
	initControllerListener();
	initMusic();

	scheduleUpdate();

	return true;
}

void VictoryScreen::initUI()
{
	//set background
	background = Sprite::create("Backgrounds/winscreen.png");
	background->setAnchorPoint(Vec2(0.0f, 0.0f));
	this->addChild(background, 1);

	textOverlay = Sprite::create("Backgrounds/uWinTest.png");
	textOverlay->setAnchorPoint(Vec2(0.0f, 0.0f));
	this->addChild(textOverlay, 2);

	mainMenuText = Sprite::create("Text/mainMenuTest.png");
	mainMenuText->setPosition(1920 / 2, 400);
	this->addChild(mainMenuText, 10);

	exitText = Sprite::create("Text/exitTest2.png");
	exitText->setPosition(1920 / 2, 200);
	this->addChild(exitText, 10);

	//set rects for label hover/click
	mainMenuRect.setRect(mainMenuText->getPositionX() - 300, mainMenuText->getPositionY() - 100, 600, 200);
	exitRect.setRect(exitText->getPositionX() - 300, exitText->getPositionY() - 100, 600, 200);

}

void VictoryScreen::initAnimations()
{
}

void VictoryScreen::initMusic()
{
	auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
	audio->resumeBackgroundMusic();
}

void VictoryScreen::initMouseListener()
{
	//Init the mouse listener
	mouseListener = EventListenerMouse::create();

	//On Mouse Down
	mouseListener->onMouseDown = CC_CALLBACK_1(VictoryScreen::mouseDownCallback, this);

	//On Mouse Up
	mouseListener->onMouseUp = CC_CALLBACK_1(VictoryScreen::mouseUpCallback, this);

	//On Mouse Move
	mouseListener->onMouseMove = CC_CALLBACK_1(VictoryScreen::mouseMoveCallback, this);

	//On Mouse Scroll
	mouseListener->onMouseScroll = CC_CALLBACK_1(VictoryScreen::mouseScrollCallback, this);

	//Add the mouse listener to the dispatcher
	_eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);
}

void VictoryScreen::initControllerListener()
{
	controllerListener = EventListenerController::create();

	//set up callbacks
	controllerListener->onKeyDown = CC_CALLBACK_3(VictoryScreen::buttonPressCallback, this);
	controllerListener->onKeyUp = CC_CALLBACK_3(VictoryScreen::buttonReleaseCallback, this);
	controllerListener->onAxisEvent = CC_CALLBACK_3(VictoryScreen::axisEventCallback, this);

	controllerListener->onConnected = [](cocos2d::Controller* controller, cocos2d::Event* evt) {};

	//add the controller listener to the dispatcher
	_eventDispatcher->addEventListenerWithSceneGraphPriority(controllerListener, this);
}

//move to the next selection on the menu
void VictoryScreen::moveToNextMenuItem()
{
	switch (currentSelection)
	{
	case MenuOptions::nothing:
		currentSelection = MenuOptions::mainMenu;
		break;

	case MenuOptions::mainMenu:
		currentSelection = MenuOptions::exit;
		break;

	case MenuOptions::exit:
		currentSelection = MenuOptions::mainMenu;
		break;
	}
}

//move back one selection on the menu
void VictoryScreen::moveToPreviousMenuItem()
{
	switch (currentSelection)
	{
	case MenuOptions::nothing:
		currentSelection = MenuOptions::mainMenu;
		break;

	case MenuOptions::mainMenu:
		currentSelection = MenuOptions::exit;
		break;

	case MenuOptions::exit:
		currentSelection = MenuOptions::mainMenu;
		break;
	}
}

void VictoryScreen::update(float dt)
{
	if (!isTransitioning)
	{
		//check for mouse hover over menu items
		if (mainMenuRect.containsPoint(cursorPos) || currentSelection == MenuOptions::mainMenu)
			mainMenuText->setScale(1.2f);
		else
			mainMenuText->setScale(1.0f);

		if (exitRect.containsPoint(cursorPos) || currentSelection == MenuOptions::exit)
			exitText->setScale(1.2f);
		else
			exitText->setScale(1.0f);
	}
}

//--- Callbacks ---//

void VictoryScreen::mouseDownCallback(Event* event)
{
	//Cast the event as a mouse event
	EventMouse* mouseEvent = dynamic_cast<EventMouse*>(event);
	auto mouseButton = mouseEvent->getMouseButton();

	//Get the position of the mouse button press
	auto mouseClickPosition = mouseEvent->getLocationInView();

	if (mouseButton == cocos2d::EventMouse::MouseButton::BUTTON_LEFT)
	{
		//open controls menu
		if (mainMenuRect.containsPoint(cursorPos))
		{
			director->replaceScene(TransitionFade::create(1.f, MainMenu::createScene(), Color3B(0, 0, 0)));
			isTransitioning = true;
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

void VictoryScreen::mouseUpCallback(Event* event)
{
}

void VictoryScreen::mouseMoveCallback(Event* event)
{
	EventMouse* mouseEvent = dynamic_cast<EventMouse*>(event);
	cursorPos = mouseEvent->getLocationInView();
	cursorPos.y += 1080;
}

void VictoryScreen::mouseScrollCallback(Event* event)
{
}

void VictoryScreen::buttonPressCallback(Controller * controller, int keyCode, Event * event)
{
	switch (keyCode)
	{
	case ControllerInput::A:
	case ControllerInput::Start:
		//start game
		if (currentSelection == MenuOptions::mainMenu)
		{
			director->replaceScene(TransitionFade::create(1.f, MainMenu::createScene(), Color3B(0, 0, 0)));
			isTransitioning = true;
		}
		//exit game
		else if (currentSelection == MenuOptions::exit)
		{
			director->end();
		}
		break;
	}
}

void VictoryScreen::buttonReleaseCallback(Controller * controller, int keyCode, Event * event)
{
}

void VictoryScreen::axisEventCallback(Controller * controller, int keyCode, Event * event)
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
