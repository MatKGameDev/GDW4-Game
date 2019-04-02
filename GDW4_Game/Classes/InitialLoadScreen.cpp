#include "InitialLoadScreen.h"
#include "MainMenu.h"

Scene * InitialLoadScreen::createScene()
{
	Scene* scene = InitialLoadScreen::create();
	return scene;
}

bool InitialLoadScreen::init()
{
	if (!Scene::init())
		return false;

	director = Director::getInstance();
	//Setting the default animation rate for the director
	director->setAnimationInterval(1.0f / 60.0f);
	director->setDisplayStats(1); //Remove this after debugging

	image = Sprite::create("Backgrounds/bootScreen.png");
	image->setAnchorPoint(Vec2(0.0f, 0.0f));
	image->setPosition(Vec2(0.0f, 0.0f));
	this->addChild(image);

	timer = 0.0f;
	isDone = false;

	scheduleUpdate();

	return true;
}

//preloads boss animations to reduce lag later on
void InitialLoadScreen::preloadAnimations()
{

}

void InitialLoadScreen::update(float dt)
{
	timer += dt;
	if (timer > 10.0f && !isDone)
	{
		isDone = true;
		director->replaceScene(TransitionFade::create(1.5f, MainMenu::createScene(), Color3B(0, 0, 0)));
	}
}