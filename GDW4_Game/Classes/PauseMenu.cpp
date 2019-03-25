#include "PauseMenu.h"
#include "Tutorial.h"
#include "Gameplay.h"
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

void PauseMenu::initUI()
{
	//set our sprite labels
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

void PauseMenu::update(float dt)
{
	if (resumeRect.containsPoint(cursorPos))
		resumeText->setScale(1.0f);
	else
		resumeText->setScale(0.8f);

	if (controlsRect.containsPoint(cursorPos))
		controlsText->setScale(1.0f);
	else
		controlsText->setScale(0.8f);

	if (exitRect.containsPoint(cursorPos))
		exitText->setScale(1.0f);
	else
		exitText->setScale(0.8f);
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