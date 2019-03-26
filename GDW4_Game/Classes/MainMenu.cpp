#include "MainMenu.h"
#include "Tutorial.h"
#include "ControlsMenu.h"

Scene * MainMenu::createScene()
{
	Scene* scene = MainMenu::create();
	return scene;
}

bool MainMenu::init()
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

void MainMenu::initUI()
{
	//set our sprite labels
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

void MainMenu::update(float dt)
{
	if (!isTransitioning)
	{
		//check for mouse hover over menu items
		if (startRect.containsPoint(cursorPos))
			startText->setScale(1.0f);
		else
			startText->setScale(0.8f);

		if (controlsRect.containsPoint(cursorPos))
			controlsText->setScale(1.0f);
		else
			controlsText->setScale(0.8f);

		if (exitRect.containsPoint(cursorPos))
			exitText->setScale(1.0f);
		else
			exitText->setScale(0.8f);
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