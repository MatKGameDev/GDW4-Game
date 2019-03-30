#pragma once
#include <base/CCEventDispatcher.h>
#include <2d/CCScene.h>

//Header Files
namespace cocos2d
{
	class EventListenerKeyboard;
	class EventListenerMouse;
	class EventListenerController;
	class EventDispatcher;
	class Scene;
}

class MouseAndKeyboardHandler
{
	//Private data members
	cocos2d::EventListenerKeyboard* keyboardListener;
	cocos2d::EventListenerMouse* mouseListener;
public:
	MouseAndKeyboardHandler(cocos2d::EventDispatcher* aEventDispatcher, cocos2d::Scene* aSceneToAdd);

	//Call back function
	void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	void onMouseButtonPressed(cocos2d::Event* event);
};