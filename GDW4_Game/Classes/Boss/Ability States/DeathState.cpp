#include "Boss/Ability States/DeathState.h"
#include <3d/CCAnimate3D.h>
#include "Animation.h"
#include "Boss/General/Boss.h"
#include "VictoryScreen.h"
#include "Hero.h"

DeathState::DeathState(Boss* bossInstance)
	: FirstBossState(bossInstance)
{
	Hero::hero->health = 100; //make sure hero doesnt die during transition
	//Get animation
	cocos2d::Animate* animation = marcos::AnimationManager::
		getAnimation("boss_death_animation_key");

	//Run action
	bossPointer->getSprite()->stopAllActions();
	bossPointer->getSprite()->runAction
	(
		cocos2d::Sequence::create
		(
			cocos2d::Repeat::create(animation, 1),
			cocos2d::DelayTime::create(3),
			cocos2d::CallFunc::create([&]{changeToVictoryScreen(); }),
			nullptr
		)
	);
}

/**
 * @brief Changes to victory scene when the boss finish
 * doing death animation
 */
void DeathState::changeToVictoryScreen()
{
	removeAllElements();
	Hero::hero->reset(); //reset hero
	cocos2d::Director::getInstance()->replaceScene
	(
		TransitionFade::create(2.0f, VictoryScreen::createScene(), Color3B(0, 0, 0))
	);
}

void DeathState::removeAllElements()
{
	auto lavaList = bossPointer->getLavaList();
	for (auto i : lavaList) {
		delete i;
	}

	bossPointer->getLavaList().clear();
}
