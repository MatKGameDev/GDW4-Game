#pragma once

namespace cocos2d
{
	class Scene;
	class EventDispatcher;
	class EventListenerController;
	class Controller;
	class Event;
}

class ControllerHandler
{
	cocos2d::EventListenerController *controllerListener;
public:
	ControllerHandler(cocos2d::EventDispatcher* aEventDispatcher, cocos2d::Scene* aSceneToAdd);

	//Callback function
	void onButtonPressed(cocos2d::Controller* controller, int keyCode, cocos2d::Event* event);
	void onButtonReleased(cocos2d::Controller* controller, int keyCode, cocos2d::Event* event);
	void onAxisMoved(cocos2d::Controller* controller, int keyCode, cocos2d::Event* event);
};