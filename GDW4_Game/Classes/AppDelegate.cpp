/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/



#include "AppDelegate.h"
#include "Gameplay.h"
#include "Tutorial.h"
#include "HeroStateManager.h"
#include "MainMenu.h"
#include "PauseMenu.h"

USING_NS_CC;

//--- Constructors and Destructors ---//
AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate()
{
}

//--- Virtual Methods ---//
bool AppDelegate::applicationDidFinishLaunching()
{
	auto director = Director::getInstance();
	auto glview = director->getOpenGLView();
	auto console = director->getConsole();

	if (!glview)
	{
		glview = GLViewImpl::createWithRect("GDW4 Game", Rect(0.0f, 0.0f, 1920.f, 1080.f), 1.0f, false);
		//glview = GLViewImpl::createWithFullScreen("GDW4 Game");
		director->setOpenGLView(glview);
	}

	Hero::hero->createHero(); //create hero (calls private constructor)
	Hero::hero->sprite->setPosition(Vec2(20.0f, 400.0f)); //set initial position
	HeroStateManager::idle->onEnter();

	Grapple::grapple->initGrapple(); //create grapple (calls private constructor)

	XinputManager::instance->create(); //create xinputmanager instance (calls private constructor)

	auto scene = Gameplay::createScene();
	director->runWithScene(scene);

	return true;
}

void AppDelegate::applicationDidEnterBackground() {
}

void AppDelegate::applicationWillEnterForeground() {
}