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

	director = Director::getInstance();
	//Setting the default animation rate for the director
	director->setAnimationInterval(1.0f / 60.0f);
	director->setDisplayStats(1); //Remove this after debugging

	initUI();
	initAnimations();
	initMouseListener();

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

void DeathScreen::update(float dt)
{
	if (!isTransitioning)
	{
		//check for mouse hover over menu items
		if (tryAgainRect.containsPoint(cursorPos))
			tryAgainText->setScale(1.0f);
		else
			tryAgainText->setScale(0.8f);

		if (mainMenuRect.containsPoint(cursorPos))
			mainMenuText->setScale(1.0f);
		else
			mainMenuText->setScale(0.8f);

		if (exitRect.containsPoint(cursorPos))
			exitText->setScale(1.0f);
		else
			exitText->setScale(0.8f);
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