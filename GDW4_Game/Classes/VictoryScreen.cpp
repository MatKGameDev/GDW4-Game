#include "VictoryScreen.h"
#include "MainMenu.h"

Scene * VictoryScreen::createScene()
{
	Scene* scene = VictoryScreen::create();
	return scene;
}

bool VictoryScreen::init()
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

void VictoryScreen::initUI()
{
	//set background
	background = Sprite::create("Backgrounds/uWinTest.png");
	background->setAnchorPoint(Vec2(0.0f, 0.0f));
	this->addChild(background, 1);

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

void VictoryScreen::update(float dt)
{
	if (!isTransitioning)
	{
		//check for mouse hover over menu items
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
			this->removeAllChildrenWithCleanup(true);
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