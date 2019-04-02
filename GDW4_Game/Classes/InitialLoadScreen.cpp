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

	image = Sprite::create("Backgrounds/bootScreen.png");
	image->setAnchorPoint(Vec2(0.0f, 0.0f));
	image->setPosition(Vec2(0.0f, 0.0f));
	this->addChild(image, 1);

	preloadAnimations();

	timer = 0.0f;
	isDone = false;

	scheduleUpdate();

	return true;
}

//preloads animations to reduce lag later on
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

	sprite = cocos2d::Sprite::create("Sprites/flame_sprite.png");
	anim = cocos2d::AnimationCache::getInstance()->getAnimation("boss_idle_animation_key");
	action = cocos2d::Animate::create(anim);
	sprite->stopAllActions();
	sprite->runAction(cocos2d::Repeat::create(action->clone(), 1));
	sprite->setPosition(500, 500);
	this->addChild(sprite, -20);

	sprite = cocos2d::Sprite::create("Sprites/flame_sprite.png");
	anim = cocos2d::AnimationCache::getInstance()->getAnimation("boss_explosive_tell_POST_animation_key");
	action = cocos2d::Animate::create(anim);
	sprite->stopAllActions();
	sprite->runAction(cocos2d::Repeat::create(action->clone(), 1));
	sprite->setPosition(500, 500);
	this->addChild(sprite, -20);

	sprite = cocos2d::Sprite::create("Sprites/flame_sprite.png");
	anim = cocos2d::AnimationCache::getInstance()->getAnimation("boss_spit_tell_PRE_animation_key");
	action = cocos2d::Animate::create(anim);
	sprite->stopAllActions();
	sprite->runAction(cocos2d::Repeat::create(action->clone(), 1));
	sprite->setPosition(500, 500);
	this->addChild(sprite, -20);

	sprite = cocos2d::Sprite::create("Sprites/flame_sprite.png");
	anim = cocos2d::AnimationCache::getInstance()->getAnimation("boss_spit_tell_POST_animation_key");
	action = cocos2d::Animate::create(anim);
	sprite->stopAllActions();
	sprite->runAction(cocos2d::Repeat::create(action->clone(), 1));
	sprite->setPosition(500, 500);
	this->addChild(sprite, -20);

	sprite = cocos2d::Sprite::create("Sprites/flame_sprite.png");
	anim = cocos2d::AnimationCache::getInstance()->getAnimation("boss_flame_tell_PRE_animation_key");
	action = cocos2d::Animate::create(anim);
	sprite->stopAllActions();
	sprite->runAction(cocos2d::Repeat::create(action->clone(), 1));
	sprite->setPosition(500, 500);
	this->addChild(sprite, -20);

	sprite = cocos2d::Sprite::create("Sprites/flame_sprite.png");
	anim = cocos2d::AnimationCache::getInstance()->getAnimation("boss_flame_tell_POST_animation_key");
	action = cocos2d::Animate::create(anim);
	sprite->stopAllActions();
	sprite->runAction(cocos2d::Repeat::create(action->clone(), 1));
	sprite->setPosition(500, 500);
	this->addChild(sprite, -20);

	sprite = cocos2d::Sprite::create("Sprites/flame_sprite.png");
	anim = cocos2d::AnimationCache::getInstance()->getAnimation("boss_idle_animation_key");
	action = cocos2d::Animate::create(anim);
	sprite->stopAllActions();
	sprite->runAction(cocos2d::Repeat::create(action->clone(), 1));
	sprite->setPosition(500, 500);
	this->addChild(sprite, -20);

	sprite = cocos2d::Sprite::create("Sprites/flame_sprite.png");
	anim = cocos2d::AnimationCache::getInstance()->getAnimation("boss_explosive_POST_animation_key");
	action = cocos2d::Animate::create(anim);
	sprite->stopAllActions();
	sprite->runAction(cocos2d::Repeat::create(action->clone(), 1));
	sprite->setPosition(500, 500);
	this->addChild(sprite, -20);

	sprite = cocos2d::Sprite::create("Sprites/flame_sprite.png");
	anim = cocos2d::AnimationCache::getInstance()->getAnimation("boss_explosive_PRE_animation_key");
	action = cocos2d::Animate::create(anim);
	sprite->stopAllActions();
	sprite->runAction(cocos2d::Repeat::create(action->clone(), 1));
	sprite->setPosition(500, 500);
	this->addChild(sprite, -20);

	sprite = cocos2d::Sprite::create("Sprites/flame_sprite.png");
	anim = cocos2d::AnimationCache::getInstance()->getAnimation("boss_flame_PRE_animation_key");
	action = cocos2d::Animate::create(anim);
	sprite->stopAllActions();
	sprite->runAction(cocos2d::Repeat::create(action->clone(), 1));
	sprite->setPosition(500, 500);
	this->addChild(sprite, -20);

	sprite = cocos2d::Sprite::create("Sprites/flame_sprite.png");
	anim = cocos2d::AnimationCache::getInstance()->getAnimation("boss_flame_MID_animation_key");
	action = cocos2d::Animate::create(anim);
	sprite->stopAllActions();
	sprite->runAction(cocos2d::Repeat::create(action->clone(), 1));
	sprite->setPosition(500, 500);
	this->addChild(sprite, -20);

	sprite = cocos2d::Sprite::create("Sprites/flame_sprite.png");
	anim = cocos2d::AnimationCache::getInstance()->getAnimation("boss_flame_POST_animation_key");
	action = cocos2d::Animate::create(anim);
	sprite->stopAllActions();
	sprite->runAction(cocos2d::Repeat::create(action->clone(), 1));
	sprite->setPosition(500, 500);
	this->addChild(sprite, -20);

	sprite = cocos2d::Sprite::create("Sprites/flame_sprite.png");
	anim = cocos2d::AnimationCache::getInstance()->getAnimation("boss_spit_animation_key");
	action = cocos2d::Animate::create(anim);
	sprite->stopAllActions();
	sprite->runAction(cocos2d::Repeat::create(action->clone(), 1));
	sprite->setPosition(500, 500);
	this->addChild(sprite, -20);

	sprite = cocos2d::Sprite::create("Backgrounds/greyBackground.png");
	anim = cocos2d::AnimationCache::getInstance()->getAnimation("main_menu_animation_key");
	action = cocos2d::Animate::create(anim);
	sprite->stopAllActions();
	sprite->runAction(cocos2d::RepeatForever::create(action->clone()));
	sprite->setAnchorPoint(Vec2(0, 0));
	sprite->setPosition(0, 0);
	this->addChild(sprite, -21);

	sprite = cocos2d::Sprite::create("Backgrounds/greyBackground.png");
	anim = cocos2d::AnimationCache::getInstance()->getAnimation("boss_death_animation_key");
	action = cocos2d::Animate::create(anim);
	sprite->stopAllActions();
	sprite->runAction(cocos2d::RepeatForever::create(action->clone()));
	sprite->setAnchorPoint(Vec2(0, 0));
	sprite->setPosition(0, 0);
	this->addChild(sprite, -21);
}

void InitialLoadScreen::update(float dt)
{
	//if (timer == 0.0f)
		//preloadAnimations();

	timer += dt;
	if (timer > 2.0f && !isDone)
	{
		isDone = true;
		director->replaceScene(TransitionFade::create(1.5f, MainMenu::createScene(), Color3B(0, 0, 0)));
	}
}