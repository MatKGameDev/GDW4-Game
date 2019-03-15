#include "AppDelegate.h"
#include "HelloWorldScene.h"

// #define USE_AUDIO_ENGINE 1
// #define USE_SIMPLE_AUDIO_ENGINE 1


USING_NS_CC;

static cocos2d::Size designResolutionSize = cocos2d::Size(480, 320);
static cocos2d::Size smallResolutionSize = cocos2d::Size(480, 320);
static cocos2d::Size mediumResolutionSize = cocos2d::Size(1024, 768);
static cocos2d::Size largeResolutionSize = cocos2d::Size(2048, 1536);

AppDelegate::AppDelegate()
{
}

AppDelegate::~AppDelegate() 
{

}


bool AppDelegate::applicationDidFinishLaunching() {
	auto director = Director::getInstance();
	auto glView = director->getOpenGLView();
	if (!glView) {
		glView = GLViewImpl::createWithRect("Hello World", cocos2d::Rect(0, 0, 1920, 1080));
		director->setOpenGLView(glView);
	}

	//auto scene = HelloWorld::createScene();
	director->runWithScene(HelloWorld::createScene());
	

	return true;
}

// This function will be called when the app is inactive. Note, when receiving a phone call it is invoked.
void AppDelegate::applicationDidEnterBackground() {

}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {

}
