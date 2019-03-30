#include "Input Handler/MouseAndKeyboardHandler.h"
#include "cocos2d.h"
#include "PauseMenu.h"
#include "HeroAttackManager.h"
#include "Hero.h"
#include "HeroStateManager.h"
#include "Grapple.h"


MouseAndKeyboardHandler::MouseAndKeyboardHandler(cocos2d::EventDispatcher* aEventDispatcher, cocos2d::Scene* aSceneToAdd)
	:keyboardListener(cocos2d::EventListenerKeyboard::create()),
	mouseListener(cocos2d::EventListenerMouse::create())
{
	//Binding keyboard callback functions to member
	keyboardListener->onKeyPressed = CC_CALLBACK_2(MouseAndKeyboardHandler::onKeyPressed, this);
	keyboardListener->onKeyReleased = CC_CALLBACK_2(MouseAndKeyboardHandler::onKeyReleased, this);
	aEventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, aSceneToAdd);

	//Binding mouse callback function to member
	mouseListener->onMouseDown = CC_CALLBACK_1(MouseAndKeyboardHandler::onMouseButtonPressed, this);
	aEventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, aSceneToAdd);
}

void MouseAndKeyboardHandler::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_A:
		HeroStateManager::currentState->handleInput(InputType::p_a);
		Hero::hero->lookState = Hero::LookDirection::lookingLeft;
		Hero::hero->moveState = Hero::MoveDirection::movingLeft;
		break;

	case EventKeyboard::KeyCode::KEY_D:
		HeroStateManager::currentState->handleInput(InputType::p_d);
		Hero::hero->lookState = Hero::LookDirection::lookingRight;
		Hero::hero->moveState = Hero::MoveDirection::movingRight;
		break;

	case EventKeyboard::KeyCode::KEY_W:
		HeroAttackBase::isWKeyHeld = true;
		break;

	case EventKeyboard::KeyCode::KEY_S:
		HeroStateManager::currentState->handleInput(InputType::p_s);
		break;

	case EventKeyboard::KeyCode::KEY_SPACE:
		HeroStateManager::currentState->handleInput(InputType::p_space);
		break;

		//ATTACKS FOR TESTING. TODO: remove later and set to proper keybinds (numbers to swap between attacks?)
	case EventKeyboard::KeyCode::KEY_Q:
		HeroAttackManager::setCurrentAttack(HeroAttackTypes::meleeFireA, nullptr); //scene can be nullptr since we dont actually add anything to the scene in melee attacks
		break;

	case EventKeyboard::KeyCode::KEY_E:
		//HeroAttackManager::setCurrentAttack(HeroAttackTypes::projectileIceA, this);
		break;

	case EventKeyboard::KeyCode::KEY_ESCAPE:
		cocos2d::Director::getInstance()->pushScene(PauseMenu::createScene());
	}
}

void MouseAndKeyboardHandler::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_A:
		//make sure the hero is moving in this direction before we decide if they are now idle
		if (Hero::hero->moveState == Hero::MoveDirection::movingLeft)
			Hero::hero->moveState = Hero::MoveDirection::idle;
		break;

	case EventKeyboard::KeyCode::KEY_D:
		//make sure the hero is moving in this direction before we decide if they are now idle
		if (Hero::hero->moveState == Hero::MoveDirection::movingRight)
			Hero::hero->moveState = Hero::MoveDirection::idle;
		break;

	case EventKeyboard::KeyCode::KEY_W:
		HeroAttackBase::isWKeyHeld = false;
		break;

	case EventKeyboard::KeyCode::KEY_SPACE:
		HeroStateManager::currentState->handleInput(InputType::r_space);
		break;
	}
}

void MouseAndKeyboardHandler::onMouseButtonPressed(cocos2d::Event* event)
{
	//Cast the event as a mouse event
	EventMouse* mouseEvent = dynamic_cast<EventMouse*>(event);
	const auto mouseButton = mouseEvent->getMouseButton();

	if (mouseButton == cocos2d::EventMouse::MouseButton::BUTTON_LEFT)
	{
		HeroAttackManager::setCurrentAttack(HeroAttackTypes::meleeFireA, nullptr); //can pass a nullptr because we dont need to add anything to the scene for melee attacks
	}
	if (mouseButton == cocos2d::EventMouse::MouseButton::BUTTON_RIGHT)
	{
		//Get the position of the mouse button press
		auto mouseClickPosition = mouseEvent->getLocationInView();
		mouseClickPosition.y += 1080;

		auto mouseGameViewPosition = mouseClickPosition;
		mouseGameViewPosition.y += 25;

		//calculate proper x position for grapple
		if (Hero::hero->getPosition().x > 1920 / 2)
		{
			//do some simple math to convert mouse click position on screen to in-game world position
			mouseGameViewPosition.x -= 1920 / 2; //update if screen size changes
			mouseGameViewPosition.x += Hero::hero->sprite->getPosition().x;
		}

		Grapple::grapple->shoot(Vect2(mouseGameViewPosition)); //shoot the grapple
	}
}
