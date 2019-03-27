#include "PrettyPictureScene.h"
#include "Gameplay.h"

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

	preloadAnimations();

	scheduleUpdate();

	return true;
}

//preloads boss animations to reduce lag on the boss scene
void PrettyPictureScene::preloadAnimations()
{
	//flamethrower attack
	auto sprite = cocos2d::Sprite::create("Sprites/flame_sprite.png");
	auto anim = cocos2d::AnimationCache::getInstance()->getAnimation("boss_flame_animation_key");
	auto action = cocos2d::Animate::create(anim);
	sprite->stopAllActions();
	sprite->runAction(cocos2d::Repeat::create(action->clone(), 1));
	sprite->setPosition(500, 500);
	this->addChild(sprite, 18);

	//3 lava ball attack
	sprite = cocos2d::Sprite::create("Sprites/spit_sprite.png");
	anim = cocos2d::AnimationCache::getInstance()->getAnimation("boss_spit_animation_key");
	action = cocos2d::Animate::create(anim);
	sprite->stopAllActions();
	sprite->runAction(cocos2d::Repeat::create(action->clone(), 1));
	sprite->setPosition(500, 500);
	this->addChild(sprite, 18);
}

void PrettyPictureScene::update(float dt)
{
	timer += dt;
	if (timer > 12.0f && !isDone)
	{
		isDone = true;
		this->removeAllChildren();
		director->replaceScene(TransitionFade::create(1.5f, Gameplay::createScene(), Color3B(0, 0, 0)));
	}
}