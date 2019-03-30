#include "Input Handler/ControllerHandler.h"
#include <base/CCEventListenerController.h>
#include "ControllerInput.h"
#include "HeroStateManager.h"
#include "PauseMenu.h"
#include "XinputManager.h"
#include "Grapple.h"
#include "HeroAttackManager.h"


ControllerHandler::ControllerHandler(cocos2d::EventDispatcher* aEventDispatcher, cocos2d::Scene* aSceneToAdd)
	: controllerListener(cocos2d::EventListenerController::create())
{
	//Binding controller callback function to member
	controllerListener->onKeyDown = CC_CALLBACK_3(ControllerHandler::onButtonPressed, this);
	controllerListener->onKeyUp = CC_CALLBACK_3(ControllerHandler::onButtonReleased, this);
	controllerListener->onAxisEvent = CC_CALLBACK_3(ControllerHandler::onAxisMoved, this);
	aEventDispatcher->addEventListenerWithSceneGraphPriority(controllerListener, aSceneToAdd);
}

void ControllerHandler::onButtonPressed(cocos2d::Controller* controller, int keyCode, cocos2d::Event* event)
{
	switch (keyCode)
	{
	case ControllerInput::A:
		HeroStateManager::currentState->handleInput(InputType::p_space);
		break;

	case ControllerInput::Start:
		cocos2d::Director::getInstance()->pushScene(PauseMenu::createScene());
		break;
	}
}

void ControllerHandler::onButtonReleased(cocos2d::Controller* controller, int keyCode, cocos2d::Event* event)
{
	switch (keyCode)
	{
	case ControllerInput::A:
		HeroStateManager::currentState->handleInput(InputType::r_space);
		break;
	}
}

void ControllerHandler::onAxisMoved(cocos2d::Controller* controller, int keyCode, cocos2d::Event* event)
{
	switch (keyCode)
	{
		//x axis of the left stick
	case ControllerInput::leftStickX:
		//moving to the left
		if (controller->getKeyStatus(keyCode).value <= -1)
		{
			ControllerInput::isLeftStickIdle = false;
			HeroStateManager::currentState->handleInput(InputType::p_a);
			Hero::hero->lookState = Hero::LookDirection::lookingLeft;
			Hero::hero->moveState = Hero::MoveDirection::movingLeft;
		}
		//moving to the right
		else if (controller->getKeyStatus(keyCode).value >= 1)
		{
			ControllerInput::isLeftStickIdle = false;
			HeroStateManager::currentState->handleInput(InputType::p_d);
			Hero::hero->lookState = Hero::LookDirection::lookingRight;
			Hero::hero->moveState = Hero::MoveDirection::movingRight;
		}
		else if (!ControllerInput::isLeftStickIdle) //not moving AND left stick isn't at rest
		{
			Hero::hero->moveState = Hero::MoveDirection::idle;
			ControllerInput::isLeftStickIdle = true;
		}
		break;

		//y axis of the left stick
	case ControllerInput::leftStickY:
		if (controller->getKeyStatus(keyCode).value >= 1)
			HeroAttackBase::isWKeyHeld = true;
		else
		{
			HeroAttackBase::isWKeyHeld = false;
			if (controller->getKeyStatus(keyCode).value <= -1)
				HeroStateManager::currentState->handleInput(InputType::p_s);
		}
		break;

	case ControllerInput::leftTrigger:
		//check for attack
		if (controller->getKeyStatus(keyCode).value >= 1 && ControllerInput::isLeftTriggerReset)
		{
			ControllerInput::isLeftTriggerReset = false;
			HeroAttackManager::setCurrentAttack(HeroAttackTypes::meleeFireA, nullptr); //can pass a nullptr because we dont need to add anything to the scene for melee attacks
		}
		else if (controller->getKeyStatus(keyCode).value <= -1)
			ControllerInput::isLeftTriggerReset = true;
		break;

	case ControllerInput::rightTrigger:
		if (controller->getKeyStatus(keyCode).value >= 1 && ControllerInput::isRightTriggerReset)
		{
			ControllerInput::isRightTriggerReset = false;

			//use xinput stuff to get a more accurate reading on the stick input than cocos' controller support
			XinputManager::instance->update();
			XinputController* controller1 = XinputManager::instance->getController(0);
			Stick sticks[2];
			controller1->getSticks(sticks);

			//calculate angle (in radians) using atan2 with the right stick's y and x values
			float grappleAngle = atan2(sticks[RS].x, sticks[RS].y);

			//check if right stick is at rest (account for reading being slightly off or controller rest not being perfectly calibrated)
			if (sticks[RS].x < 0.1 && sticks[RS].x > -0.1 && sticks[RS].y <= 0.1f && sticks[RS].y > -0.1f)
			{
				//calculate angle (in radians) using atan2 with the right stick's y and x values
				grappleAngle = atan2(0.0f, 0.0f);
			}
			Grapple::grapple->shoot(grappleAngle); //shoot grapple
		}
		else if (controller->getKeyStatus(keyCode).value <= -1)
			ControllerInput::isRightTriggerReset = true;
		break;
	}
}
