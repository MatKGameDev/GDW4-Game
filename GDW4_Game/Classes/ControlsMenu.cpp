#include "ControlsMenu.h"

Scene * ControlsMenu::createScene()
{
	Scene* scene = ControlsMenu::create();
	return scene;
}

bool ControlsMenu::init()
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
	initControllerListener();

	scheduleUpdate();

	return true;
}

void ControlsMenu::initUI()
{
	//set controls list image
	controlsList = Sprite::create("Backgrounds/controlsListTest.png");
	controlsList->setPosition(1920 / 2, 1080 / 2 + 120);
	this->addChild(controlsList, 7);

	//set our sprite labels
	backText = Sprite::create("Text/backTest.png");
	backText->setPosition(200, 100);
	this->addChild(backText, 10);

	//set rects for label hover/click
	backRect.setRect(backText->getPositionX() - 200, backText->getPositionY() - 100, 400, 200);
}

void ControlsMenu::initAnimations()
{
}

void ControlsMenu::initMouseListener()
{
	//Init the mouse listener
	mouseListener = EventListenerMouse::create();

	//On Mouse Down
	mouseListener->onMouseDown = CC_CALLBACK_1(ControlsMenu::mouseDownCallback, this);

	//On Mouse Up
	mouseListener->onMouseUp = CC_CALLBACK_1(ControlsMenu::mouseUpCallback, this);

	//On Mouse Move
	mouseListener->onMouseMove = CC_CALLBACK_1(ControlsMenu::mouseMoveCallback, this);

	//On Mouse Scroll
	mouseListener->onMouseScroll = CC_CALLBACK_1(ControlsMenu::mouseScrollCallback, this);

	//Add the mouse listener to the dispatcher
	_eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);
}

void ControlsMenu::initControllerListener()
{
	controllerListener = EventListenerController::create();

	//set up callbacks
	controllerListener->onKeyDown = CC_CALLBACK_3(ControlsMenu::buttonPressCallback, this);

	controllerListener->onConnected = [](cocos2d::Controller* controller, cocos2d::Event* evt) {};

	//add the controller listener to the dispatcher
	_eventDispatcher->addEventListenerWithSceneGraphPriority(controllerListener, this);
}

void ControlsMenu::update(float dt)
{
	if (backRect.containsPoint(cursorPos))
		backText->setScale(1.2f);
	else
		backText->setScale(1.0f);
}


//--- Callbacks ---//

void ControlsMenu::mouseDownCallback(Event* event)
{
	//Cast the event as a mouse event
	EventMouse* mouseEvent = dynamic_cast<EventMouse*>(event);
	auto mouseButton = mouseEvent->getMouseButton();

	//Get the position of the mouse button press
	auto mouseClickPosition = mouseEvent->getLocationInView();

	if (mouseButton == cocos2d::EventMouse::MouseButton::BUTTON_LEFT)
	{
		//go back to previous scene
		if (backRect.containsPoint(cursorPos))
		{
			director->popScene();
		}		
	}
	if (mouseButton == cocos2d::EventMouse::MouseButton::BUTTON_RIGHT)
	{

	}
}

void ControlsMenu::mouseUpCallback(Event* event)
{
}

void ControlsMenu::mouseMoveCallback(Event* event)
{
	EventMouse* mouseEvent = dynamic_cast<EventMouse*>(event);
	cursorPos = mouseEvent->getLocationInView();
	cursorPos.y += 1080;
}

void ControlsMenu::mouseScrollCallback(Event* event)
{
}

void ControlsMenu::buttonPressCallback(Controller * controller, int keyCode, Event * event)
{
	if (keyCode == ControllerInput::A || keyCode == ControllerInput::B || keyCode == ControllerInput::Back)
		director->popScene();
}
