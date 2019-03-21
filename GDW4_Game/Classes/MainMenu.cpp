#include "MainMenu.h"

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

	scheduleUpdate();

	return true;
}

void MainMenu::initUI()
{
	background = Sprite::create("Backgrounds/menuScreenTest.png");
}

void MainMenu::initAnimations()
{
}

void MainMenu::update(float dt)
{
}
