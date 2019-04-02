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
	//flamethrower attack
	auto sprite = cocos2d::Sprite::create("Sprites/flame_sprite.png");
	auto anim = cocos2d::AnimationCache::getInstance()->getAnimation("boss_explosive_tell_PRE_animation_key");
	auto action = cocos2d::Animate::create(anim);
	sprite->stopAllActions();
	sprite->runAction(cocos2d::Repeat::create(action->clone(), 1));
	sprite->setPosition(500, 500);
	this->addChild(sprite, -20);

	anim = cocos2d::AnimationCache::getInstance()->getAnimation("boss_idle_animation_key");
	action = cocos2d::Animate::create(anim);
	sprite->stopAllActions();
	sprite->runAction(cocos2d::Repeat::create(action->clone(), 1));

}

void InitialLoadScreen::update(float dt)
{
	if (timer == 0.0f)
		preloadAnimations();

	timer += dt;
	if (timer > 2.0f && !isDone)
	{
		isDone = true;
		director->replaceScene(TransitionFade::create(1.5f, MainMenu::createScene(), Color3B(0, 0, 0)));
	}
}