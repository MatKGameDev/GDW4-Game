#include "Animation.h"


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//																																			  //
//															Animation Class																	  //
//																																			  //
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void marcos::AnimationManager::init()
{
	//Hero Movement Animations
	addAnimation("Sprites/idle_right.png", 20, 75, 135, "idle_right_animation_key");
	addAnimation("Sprites/idle_left.png", 20, 75, 135, "idle_left_animation_key");
	addAnimation("Sprites/running_right.png", 6, 105, 135, "running_right_animation_key");
	addAnimation("Sprites/running_left.png", 6, 105, 135, "running_left_animation_key");
	addAnimation("Sprites/jump_right.png", 15, 105, 135, "jumping_right_animation_key");
	addAnimation("Sprites/jump_left.png", 15, 105, 135, "jumping_left_animation_key");
	addAnimation("Sprites/falling_right.png", 14, 105, 135, "falling_right_animation_key");
	addAnimation("Sprites/falling_left.png", 14, 105, 135, "falling_left_animation_key");

	//Hero Attacking Animations
	addAnimation("Sprites/melee_right.png", 4, 177, 138, "melee_right_animation_key");
	addAnimation("Sprites/melee_left.png", 4, 177, 138, "melee_left_animation_key");
	addAnimation("Sprites/melee_up_right.png", 4, 135, 260, "melee_up_right_animation_key");
	addAnimation("Sprites/melee_up_left.png", 4, 135, 260, "melee_up_left_animation_key");

	//Hero Grappling Animations
	addAnimation("Sprites/grapple_right.png", 6, 105, 135, "grapple_right_animation_key");
	addAnimation("Sprites/grapple_left.png", 6, 105, 135, "grapple_left_animation_key");
	addAnimation("Sprites/shooting_grapple_right.png", 2, 120, 135, "shooting_grapple_right_animation_key");
	addAnimation("Sprites/shooting_grapple_left.png", 2, 120, 135, "shooting_grapple_left_animation_key");
	addAnimation("Sprites/grapple_jump_right.png", 5, 120, 135, "grapple_jump_right_animation_key");
	addAnimation("Sprites/grapple_jump_left.png", 5, 120, 135, "grapple_jump_left_animation_key");
	addAnimation("Sprites/grapple_hold_right.png", 1, 105, 195, "grapple_hold_right_animation_key");
	addAnimation("Sprites/grapple_hold_left.png", 1, 105, 195, "grapple_hold_left_animation_key");

	//Hero Death Animations
	addAnimation("Sprites/death_left.png", 25, 168, 135, "hero_death_left_animation_key");
	addAnimation("Sprites/death_right.png", 25, 168, 135, "hero_death_right_animation_key");


	addAnimation("Backgrounds/mainMenu.png", 4, 7, 1920, 1080, "main_menu_animation_key");

	//Boss State Animations
	initBossStateAnimation();

	//Boss attack projectile Animations
	initBossAttackParticleAnimation();
}

/**
 * @brief This function adds all the boss state to animation cache
 */
void marcos::AnimationManager::initBossStateAnimation()
{
	const int bossHeight{ 1300 }, bossWidth{ 500 };

	addAnimation("Sprites/boss_flamethrow_part1.png", 12, bossWidth, bossHeight, "boss_flame_tell_PRE_animation_key");
	addAnimation("Sprites/boss_flamethrow_part2.png", 5, bossWidth, bossHeight, "boss_flame_tell_POST_animation_key");
	addAnimation("Sprites/boss_projectile_attack_part1.png", 14, bossWidth, bossHeight, "boss_spit_tell_PRE_animation_key");
	addAnimation("Sprites/Spit_attack_part2.png", 9, bossWidth, bossHeight, "boss_spit_tell_POST_animation_key");
	addAnimation("Sprites/boss_explosive_attack_part1.png", 8, bossWidth, bossHeight, "boss_explosive_tell_PRE_animation_key");
	addAnimation("Sprites/boss_explosive_attack_part2.png", 4, bossWidth, bossHeight, "boss_explosive_tell_POST_animation_key");
	addAnimation("Sprites/boss_idle.png", 8, 5, bossWidth, bossHeight, "boss_idle_animation_key");
	addAnimation("Sprites/BossDeathGame.png", 12, 4, bossWidth + 150, bossHeight, "boss_death_animation_key");
	addAnimation("Sprites/boss_resting.png", 16, bossWidth, bossHeight, "boss_restinga_animation_key");
}

/**
 * @brief This function adds all the boss attack particles to animation cache
 */
void marcos::AnimationManager::initBossAttackParticleAnimation()
{
	addAnimation("Sprites/exploding_fireball.png", 6, 60, 60, "boss_explosive_PRE_animation_key");
	addAnimation("Sprites/exploding_fireballpart2.png", 17, 60, 60, "boss_explosive_MID_animation_key");
	addAnimation("Sprites/exploding_fireballpart3.png", 8, 120, 120, "boss_explosive_POST_animation_key");
	addAnimation("Sprites/flame_1.png", 2, 2, 1920, 500, "boss_flame_PRE_animation_key");
	addAnimation("Sprites/flame_2.png", 4, 2, 1920, 500, "boss_flame_MID_animation_key");
	addAnimation("Sprites/flame_3.png", 4, 2, 1920, 500, "boss_flame_POST_animation_key");
	addAnimation("Sprites/fire_ball.png", 12, 70, 70, "boss_spit_animation_key");
}


//Animation setter, to store the animation frames in the animation cache to be called later
void marcos::AnimationManager::addAnimation(const std::string fileName, const int a_NumFrames, const float a_Width, const float a_Height, const std::string& keyName,
	const float a_Delay)
{
	cocos2d::Vector<cocos2d::SpriteFrame*> m_AnimFrames;

	for (int i = 0; i < a_NumFrames; i++)
	{
		auto frame = cocos2d::SpriteFrame::create(fileName, cocos2d::Rect(a_Width * i, 3, a_Width, a_Height));
		m_AnimFrames.pushBack(frame);
	}

	auto animation = cocos2d::Animation::createWithSpriteFrames(m_AnimFrames, a_Delay);
	addAnimation(animation, keyName);
}

/**
 * @brief This function set the animation from the file and add it onto the animation cache
 */
void marcos::AnimationManager::addAnimation(const std::string fileName, const int a_RowFrames, const int a_rows, const float a_Width, const float a_Height,
	const std::string& keyName, const float a_Delay)
{
	cocos2d::Vector<cocos2d::SpriteFrame*> m_AnimFrames;

	for (int i = 0; i < a_rows; i++)
	{
		for (int j = 0; j < a_RowFrames && j < 8; j++)
		{
			auto frame = cocos2d::SpriteFrame::create(fileName, cocos2d::Rect(a_Width * j, a_Height * i, a_Width, a_Height));
			m_AnimFrames.pushBack(frame);
		}
	}

	auto animation = cocos2d::Animation::createWithSpriteFrames(m_AnimFrames, a_Delay);
	addAnimation(animation, keyName);
}

/**
 *
 */
void marcos::AnimationManager::addAnimation(Animation* animationToAdd, const std::string& animationKey)
{
	AnimationCache::getInstance()->addAnimation(animationToAdd, animationKey);
}



/**
 * This static function will create an animation based on the animation key
 * @param animationKey The name of the key to create animation from
 * 
 * @return Return the cocos2d::Animate pointer
 */
cocos2d::Animate* marcos::AnimationManager::getAnimation(const std::string& animationKey)
{
	return Animate::create(AnimationCache::getInstance()->getAnimation(animationKey));
}

/**
 * This function will create an animation based on the animation key
 * and change the total animation time based on value
 * 
 * @param animationKey The key string for animation
 * @param animationTime The total animation time for the animation
 * 
 * @return Return the cocos2d::Animate pointer
 */
cocos2d::Animate* marcos::AnimationManager::getAnimationWithAnimationTime(const std::string& animationKey,
	const float& animationTime)
{
	const float delay = animationTime/ AnimationCache::getInstance()->getAnimation(animationKey)->getFrames().size();
	AnimationCache::getInstance()->getAnimation(animationKey)->setDelayPerUnit(delay);
	return getAnimation(animationKey);
}


