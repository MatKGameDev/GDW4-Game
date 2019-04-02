#include "Boss/Ability States/RestingState.h"
#include "Boss/General/Boss.h"

RestingState::RestingState(Boss* aBossInstance)
	:FirstBossState(aBossInstance), onTime(5.f)
{
	//Get animation
	cocos2d::Animate* animation =  marcos::AnimationManager::getAnimation("boss_idle_animation_key");
	//Run action
	bossPointer->getSprite()->runAction(cocos2d::RepeatForever::create(animation));
	
}

/**
 * @brief Reduce the onTime for the state
 * @param deltaTime The change of time from last frame to current frame
 */
void RestingState::update(const float& deltaTime)
{
	onTime -= deltaTime;
	if (onTime <= 0)
		changeToIdleState();
}
