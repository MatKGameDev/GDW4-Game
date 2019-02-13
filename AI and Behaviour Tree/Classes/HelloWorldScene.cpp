#include "HelloWorldScene.h"


USING_NS_CC;

Scene* HelloWorld::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();
	auto layer = HelloWorld::create();

	scene->addChild(layer);

	return scene;
}

bool HelloWorld::init()
{
	if (!Scene::init())
	{
		return false;
	}

	firstBoss = new Boss;
	firstBoss->getSprite()->setPosition(0, 0);
	firstBoss->getSprite()->setAnchorPoint(Vec2(0, 0));

	addChild(firstBoss->getSprite());

	//attack = new LavaBall(Vec2(1000, 0), Vec2(100, 500));

	this->scheduleUpdate();
	return true;
}

void HelloWorld::update(float delta)
{
	firstBoss->update(delta, cocos2d::Vec2(1000, 0));
}
