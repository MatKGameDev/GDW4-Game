#include "PrettyPictureScene.h"
#include "Boss1Scene.h"

Scene * PrettyPictureScene::createScene()
{
	Scene* scene = PrettyPictureScene::create();
	return scene;
}

bool PrettyPictureScene::init()
{
	if (!Scene::init())
		return false;

	director = Director::getInstance();
	//Setting the default animation rate for the director
	director->setAnimationInterval(1.0f / 60.0f);
	director->setDisplayStats(1); //Remove this after debugging

	image = Sprite::create("Backgrounds/cutscene.png");
	image->setAnchorPoint(Vec2(0.0f, 0.0f));
	image -> setPosition(Vec2(0.0f, 0.0f));
	this->addChild(image);

	timer = 0.0f;
	isDone = false;

	scheduleUpdate();

	return true;
}

void PrettyPictureScene::update(float dt)
{
	timer += dt;
	if (timer > 10.0f && !isDone)
	{
		isDone = true;
		director->replaceScene(TransitionFade::create(1.5f, Boss1Scene::createScene(), Color3B(0, 0, 0)));
	}
}