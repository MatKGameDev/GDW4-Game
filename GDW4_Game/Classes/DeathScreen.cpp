#include "DeathScreen.h"
#include "MainMenu.h"
#include "Tutorial.h"
#include "Gameplay.h"

Scene * DeathScreen::createScene()
{
	Scene* scene = DeathScreen::create();
	return scene;
}

bool DeathScreen::init()
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

void DeathScreen::initUI()
{
	//set background
	background = Sprite::create("Backgrounds/uLoseTest.png");
	background->setAnchorPoint(Vec2(0.0f, 0.0f));
	this->addChild(background, 1);

	//set our sprite labels
	tryAgainText = Sprite::create("Text/tryAgainTest.png");
	tryAgainText->setPosition(1920 / 2, 600);
	this->addChild(tryAgainText, 10);

	mainMenuText = Sprite::create("Text/mainMenuTest.png");
	mainMenuText->setPosition(1920 / 2, 400);
	this->addChild(mainMenuText, 10);

	exitText = Sprite::create("Text/exitTest2.png");
	exitText->setPosition(1920 / 2, 200);
	this->addChild(exitText, 10);

	//set rects for label hover/click
	tryAgainRect.setRect(tryAgainText->getPositionX() - 300, tryAgainText->getPositionY() - 100, 600, 200);
	mainMenuRect.setRect(mainMenuText->getPositionX() - 300, mainMenuText->getPositionY() - 100, 600, 200);
	exitRect.setRect(exitText->getPositionX() - 300, exitText->getPositionY() - 100, 600, 200);

}

void DeathScreen::initAnimations()
{
}

void DeathScreen::initMouseListener()
{
	//Init the mouse listener
	mouseListener = EventListenerMouse::create();

	//On Mouse Down
	mouseListener->onMouseDown = CC_CALLBACK_1(DeathScreen::mouseDownCallback, this);

	//On Mouse Up
	mouseListener->onMouseUp = CC_CALLBACK_1(DeathScreen::mouseUpCallback, this);

	//On Mouse Move
	mouseListener->onMouseMove = CC_CALLBACK_1(DeathScreen::mouseMoveCallback, this);

	//On Mouse Scroll
	mouseListener->onMouseScroll = CC_CALLBACK_1(DeathScreen::mouseScrollCallback, this);

	//Add the mouse listener to the dispatcher
	_eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);
}

void DeathScreen::initControllerListener()
{
	controllerListener = EventListenerController::create();

	//set up callbacks
	controllerListener->onKeyDown = CC_CALLBACK_3(DeathScreen::buttonPressCallback, this);
	controllerListener->onKeyUp = CC_CALLBACK_3(DeathScreen::buttonReleaseCallback, this);
	controllerListener->onAxisEvent = CC_CALLBACK_3(DeathScreen::axisEventCallback, this);

	controllerListener->onConnected = [](cocos2d::Controller* controller, cocos2d::Event* evt) {};

	//add the controller listener to the dispatcher
	_eventDispatcher->addEventListenerWithSceneGraphPriority(controllerListener, this);
}

//move to the next selection on the menu
void DeathScreen::moveToNextMenuItem()
{
	switch (currentSelection)
	{
	case MenuOptions::nothing:
		currentSelection = MenuOptions::tryAgain;
		break;

	case MenuOptions::tryAgain:
		currentSelection = MenuOptions::mainMenu;
		break;

	case MenuOptions::mainMenu:
		currentSelection = MenuOptions::exit;
		break;

	case MenuOptions::exit:
		currentSelection = MenuOptions::tryAgain;
		break;
	}
}

//move back one selection on the menu
void DeathScreen::moveToPreviousMenuItem()
{
	switch (currentSelection)
	{
	case MenuOptions::nothing:
		currentSelection = MenuOptions::tryAgain;
		break;

	case MenuOptions::tryAgain:
		currentSelection = MenuOptions::exit;
		break;

	case MenuOptions::mainMenu:
		currentSelection = MenuOptions::tryAgain;
		break;

	case MenuOptions::exit:
		currentSelection = MenuOptions::mainMenu;
		break;
	}
}

void DeathScreen::update(float dt)
{
	if (!isTransitioning)
	{
		//check for mouse hover over menu items
		if (tryAgainRect.containsPoint(cursorPos) || currentSelection == MenuOptions::tryAgain)
			tryAgainText->setScale(1.2f);
		else
			tryAgainText->setScale(1.0f);

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

void DeathScreen::mouseDownCallback(Event* event)
{
	//Cast the event as a mouse event
	EventMouse* mouseEvent = dynamic_cast<EventMouse*>(event);
	auto mouseButton = mouseEvent->getMouseButton();

	//Get the position of the mouse button press
	auto mouseClickPosition = mouseEvent->getLocationInView();

	if (mouseButton == cocos2d::EventMouse::MouseButton::BUTTON_LEFT)
	{
		//start game
		if (tryAgainRect.containsPoint(cursorPos))
		{
			director->replaceScene(TransitionFade::create(1.f, Tutorial::createScene(), Color3B(0, 0, 0)));
			isTransitioning = true;
		}
		//open controls menu
		else if (mainMenuRect.containsPoint(cursorPos))
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

void DeathScreen::mouseUpCallback(Event* event)
{
}

void DeathScreen::mouseMoveCallback(Event* event)
{
	EventMouse* mouseEvent = dynamic_cast<EventMouse*>(event);
	cursorPos = mouseEvent->getLocationInView();
	cursorPos.y += 1080;
}

void DeathScreen::mouseScrollCallback(Event* event)
{
}

void DeathScreen::buttonPressCallback(Controller * controller, int keyCode, Event * event)
{
	switch (keyCode)
	{
	case ControllerInput::A:
	case ControllerInput::Start:
		//start game
		if (currentSelection == MenuOptions::tryAgain)
		{
			director->replaceScene(TransitionFade::create(1.f, Tutorial::createScene(), Color3B(0, 0, 0)));
			isTransitioning = true;
		}
		//open controls menu
		else if (currentSelection == MenuOptions::mainMenu)
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

void DeathScreen::buttonReleaseCallback(Controller * controller, int keyCode, Event * event)
{
}

void DeathScreen::axisEventCallback(Controller * controller, int keyCode, Event * event)
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
