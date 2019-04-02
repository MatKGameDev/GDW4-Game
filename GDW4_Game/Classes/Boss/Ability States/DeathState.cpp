#include "Boss/Ability States/DeathState.h"
#include <3d/CCAnimate3D.h>
#include "Animation.h"
#include "Boss/General/Boss.h"
#include "VictoryScreen.h"

DeathState::DeathState(Boss* bossInstance)
	: FirstBossState(bossInstance)
{
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
	cocos2d::Director::getInstance()->replaceScene
	(
		TransitionFade::create(2.0f, VictoryScreen::createScene(), Color3B(0, 0, 0))
	);
}
