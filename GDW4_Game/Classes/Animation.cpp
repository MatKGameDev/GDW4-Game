#include "Animation.h"

//static variable initialization

//Idling
cocos2d::Animation* marcos::AnimationManager::m_IdlingLeftAnimation = new cocos2d::Animation();
cocos2d::Animation* marcos::AnimationManager::m_IdlingRightAnimation = new cocos2d::Animation();

//Running
cocos2d::Animation* marcos::AnimationManager::m_RunningRightAnimation = new cocos2d::Animation();
cocos2d::Animation* marcos::AnimationManager::m_RunningLeftAnimation = new cocos2d::Animation();

//Jumping
cocos2d::Animation* marcos::AnimationManager::m_JumpingRightAnimation = new cocos2d::Animation();
cocos2d::Animation* marcos::AnimationManager::m_JumpingLeftAnimation = new cocos2d::Animation();

cocos2d::Animation* marcos::AnimationManager::m_FallingRightAnimation = new cocos2d::Animation();
cocos2d::Animation* marcos::AnimationManager::m_FallingLeftAnimation = new cocos2d::Animation();

//Attacking
cocos2d::Animation* marcos::AnimationManager::m_MeleeAttackRightAnimation = new cocos2d::Animation();
cocos2d::Animation* marcos::AnimationManager::m_MeleeAttackLeftAnimation = new cocos2d::Animation();

cocos2d::Animation* marcos::AnimationManager::m_MeleeAttackUpRightAnimation = new cocos2d::Animation();
cocos2d::Animation* marcos::AnimationManager::m_MeleeAttackUpLeftAnimation = new cocos2d::Animation();

//Grappling
cocos2d::Animation* marcos::AnimationManager::m_GrapplingRightAnimation = new cocos2d::Animation();
cocos2d::Animation* marcos::AnimationManager::m_GrapplingLeftAnimation = new cocos2d::Animation();

cocos2d::Animation* marcos::AnimationManager::m_ShootingGrappleLeftAnimation = new cocos2d::Animation();
cocos2d::Animation* marcos::AnimationManager::m_ShootingGrappleRightAnimation = new cocos2d::Animation();

cocos2d::Animation* marcos::AnimationManager::m_GrappleJumpRightAnimation = new cocos2d::Animation();
cocos2d::Animation* marcos::AnimationManager::m_GrappleJumpLeftAnimation = new cocos2d::Animation();

cocos2d::Animation* marcos::AnimationManager::m_GrappleHoldRightAnimation = new cocos2d::Animation();
cocos2d::Animation* marcos::AnimationManager::m_GrappleHoldLeftAnimation = new cocos2d::Animation();


//boss

cocos2d::Animation* marcos::AnimationManager::m_BossFlameAnimationPRE = new cocos2d::Animation();
cocos2d::Animation* marcos::AnimationManager::m_BossFlameAnimationMID = new cocos2d::Animation();
cocos2d::Animation* marcos::AnimationManager::m_BossFlameAnimationPOST = new cocos2d::Animation();

cocos2d::Animation* marcos::AnimationManager::m_BossFlameTellAnimationPRE = new cocos2d::Animation();
cocos2d::Animation* marcos::AnimationManager::m_BossFlameTellAnimationPOST = new cocos2d::Animation();

cocos2d::Animation* marcos::AnimationManager::m_BossSpitAnimation = new cocos2d::Animation();

cocos2d::Animation* marcos::AnimationManager::m_BossSpitTellAnimationPRE = new cocos2d::Animation();
cocos2d::Animation* marcos::AnimationManager::m_BossSpitTellAnimationPOST = new cocos2d::Animation();

cocos2d::Animation* marcos::AnimationManager::m_BossExplosiveTellAnimationPRE = new cocos2d::Animation();
cocos2d::Animation* marcos::AnimationManager::m_BossExplosiveTellAnimationPOST = new cocos2d::Animation();

cocos2d::Animation* marcos::AnimationManager::m_BossExplosionAnimationPRE = new cocos2d::Animation();
cocos2d::Animation* marcos::AnimationManager::m_BossExplosionAnimationPOST = new cocos2d::Animation();

cocos2d::Animation* marcos::AnimationManager::m_BossIdleAnimation = new cocos2d::Animation();

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//																																			  //
//															Animation Class																	  //
//																																			  //
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

marcos::AnimationManager::AnimationManager()
{

}

marcos::AnimationManager::~AnimationManager()
{

}

void marcos::AnimationManager::init()
{
	/////////////////////////////////////// I D L I N G ///////////////////////////////////////////////
	m_IdlingRightAnimation = setAnimation("Sprites/idle_right.png", 20, 75, 135, 0.1f);
	AnimationCache::getInstance()->addAnimation(m_IdlingRightAnimation, "idle_right_animation_key");

	m_IdlingLeftAnimation = setAnimation("Sprites/idle_left.png", 20, 75, 135, 0.2f);
	AnimationCache::getInstance()->addAnimation(m_IdlingLeftAnimation, "idle_left_animation_key");

	/////////////////////////////////////// R U N N I N G /////////////////////////////////////////////
	m_RunningRightAnimation = setAnimation("Sprites/running_right.png", 6, 105, 135, 0.1f);
	AnimationCache::getInstance()->addAnimation(m_RunningRightAnimation, "running_right_animation_key");

	m_RunningLeftAnimation = setAnimation("Sprites/running_left.png", 6, 105, 135, 0.1f);
	AnimationCache::getInstance()->addAnimation(m_RunningLeftAnimation, "running_left_animation_key");

	/////////////////////////////////////// J U M P I N G ////////////////////////////////////////////
	m_JumpingRightAnimation = setAnimation("Sprites/jump_right.png", 15, 105, 135, 0.1f);
	AnimationCache::getInstance()->addAnimation(m_JumpingRightAnimation, "jumping_right_animation_key");

	m_JumpingLeftAnimation = setAnimation("Sprites/jump_left.png", 15, 105, 135, 0.1f);
	AnimationCache::getInstance()->addAnimation(m_JumpingLeftAnimation, "jumping_left_animation_key");


	m_FallingRightAnimation = setAnimation("Sprites/falling_right.png", 14, 105, 135, 0.1f);
	AnimationCache::getInstance()->addAnimation(m_FallingRightAnimation, "falling_right_animation_key");

	m_FallingLeftAnimation = setAnimation("Sprites/falling_left.png", 14, 105, 135,  0.1f);
	AnimationCache::getInstance()->addAnimation(m_FallingLeftAnimation, "falling_left_animation_key");


	/////////////////////////////////////// A T T A C K I N G /////////////////////////////////////////
	m_MeleeAttackRightAnimation = setAnimation("Sprites/melee_right.png", 4, 177, 138, 0.1f);
	AnimationCache::getInstance()->addAnimation(m_MeleeAttackRightAnimation, "melee_right_animation_key");

	m_MeleeAttackLeftAnimation = setAnimation("Sprites/melee_left.png", 4, 177, 135, 0.1f);
	AnimationCache::getInstance()->addAnimation(m_MeleeAttackLeftAnimation, "melee_left_animation_key");


	m_MeleeAttackUpRightAnimation = setAnimation("Sprites/melee_up_right.png", 4, 135, 260, 0.1f);
	AnimationCache::getInstance()->addAnimation(m_MeleeAttackUpRightAnimation, "melee_up_right_animation_key");

	m_MeleeAttackUpLeftAnimation = setAnimation("Sprites/melee_up_left.png", 4, 135, 260, 0.1f);
	AnimationCache::getInstance()->addAnimation(m_MeleeAttackUpLeftAnimation, "melee_up_left_animation_key");


	/////////////////////////////////////// G R A P P L I N G /////////////////////////////////////////
	m_GrapplingRightAnimation = setAnimation("Sprites/grapple_right.png", 6, 105, 135, 0.1f);
	AnimationCache::getInstance()->addAnimation(m_GrapplingRightAnimation, "grapple_right_animation_key");

	m_GrapplingLeftAnimation = setAnimation("Sprites/grapple_left.png", 6, 105, 135, 0.1f);
	AnimationCache::getInstance()->addAnimation(m_GrapplingLeftAnimation, "grapple_left_animation_key");


	m_ShootingGrappleLeftAnimation = setAnimation("Sprites/shooting_grapple_right.png", 2, 120, 135, 0.1f);
	AnimationCache::getInstance()->addAnimation(m_ShootingGrappleLeftAnimation, "shooting_grapple_right_animation_key");

	m_ShootingGrappleRightAnimation = setAnimation("Sprites/shooting_grapple_left.png", 2, 120, 135, 0.1f);
	AnimationCache::getInstance()->addAnimation(m_ShootingGrappleRightAnimation, "shooting_grapple_left_animation_key");


	m_GrappleJumpRightAnimation = setAnimation("Sprites/grapple_jump_right.png", 5, 120, 135, 0.1f);
	AnimationCache::getInstance()->addAnimation(m_GrappleJumpRightAnimation, "grapple_jump_right_animation_key");

	m_GrappleJumpLeftAnimation = setAnimation("Sprites/grapple_jump_left.png", 5, 120, 135, 0.1f);
	AnimationCache::getInstance()->addAnimation(m_GrappleJumpLeftAnimation, "grapple_jump_left_animation_key");
	

	m_GrappleHoldRightAnimation = setAnimation("Sprites/grapple_hold_right.png", 1, 105, 195, 0.1f);
	AnimationCache::getInstance()->addAnimation(m_GrappleHoldRightAnimation, "grapple_hold_right_animation_key");

	m_GrappleHoldLeftAnimation = setAnimation("Sprites/grapple_hold_left.png", 1, 105, 195, 0.1f);
	AnimationCache::getInstance()->addAnimation(m_GrappleHoldLeftAnimation, "grapple_hold_left_animation_key");


	
	//////////////////////////////////////////// B O S S ///////////////////////////////////////////

	m_BossFlameTellAnimationPRE = setAnimation("Sprites/boss_flamethrow_part1.png", 12, 500, 1300, 0.1f);
	AnimationCache::getInstance()->addAnimation(m_BossFlameTellAnimationPRE, "boss_flame_tell_PRE_animation_key");

	m_BossFlameTellAnimationPOST = setAnimation("Sprites/boss_flamethrow_part2.png", 5, 500, 1300, 0.1f);
	AnimationCache::getInstance()->addAnimation(m_BossFlameTellAnimationPOST, "boss_flame_tell_POST_animation_key");

	m_BossFlameAnimationPRE = setAnimation("Sprites/Flame1.png", 2, 2, 1920, 500, 0.1f);
	AnimationCache::getInstance()->addAnimation(m_BossFlameAnimationPRE, "boss_flame_PRE_animation_key");

	m_BossFlameAnimationMID = setAnimation("Sprites/Flame2.png", 4, 2, 1920, 500, 0.1f);
	AnimationCache::getInstance()->addAnimation(m_BossFlameAnimationMID, "boss_flame_MID_animation_key");

	m_BossFlameAnimationPOST = setAnimation("Sprites/Flame3.png", 4, 2, 1920, 500, 0.1f);
	AnimationCache::getInstance()->addAnimation(m_BossFlameAnimationPOST, "boss_flame_POST_animation_key");

	m_BossSpitAnimation = setAnimation("Sprites/fire_ball.png", 12, 70, 70, 0.1f);
	AnimationCache::getInstance()->addAnimation(m_BossSpitAnimation, "boss_spit_animation_key");

	m_BossSpitTellAnimationPRE = setAnimation("Sprites/boss_projectile_attack_part1.png", 14, 500, 1300, 0.1f);
	AnimationCache::getInstance()->addAnimation(m_BossSpitTellAnimationPRE, "boss_spit_tell_PRE_animation_key");

	m_BossSpitTellAnimationPOST = setAnimation("Sprites/Spit_attack_part2.png", 9, 500, 1300, 0.1f);
	AnimationCache::getInstance()->addAnimation(m_BossSpitTellAnimationPOST, "boss_spit_tell_POST_animation_key");

	//// @mike its these ones 
	m_BossExplosionAnimationPRE = setAnimation("Sprites/exploding_fireball.png", 6, 60, 60, 0.1f);
	AnimationCache::getInstance()->addAnimation(m_BossExplosionAnimationPRE, "boss_explosive_PRE_animation_key");

	m_BossExplosionAnimationPOST = setAnimation("Sprites/exploding_fireball_part2.png", 22, 120, 120, 0.1f);
	AnimationCache::getInstance()->addAnimation(m_BossExplosionAnimationPOST, "boss_explosive_POST_animation_key");

	m_BossExplosiveTellAnimationPRE = setAnimation("Sprites/boss_explosive_attack_part1.png", 8, 500, 1300, 0.1f);
	AnimationCache::getInstance()->addAnimation(m_BossExplosiveTellAnimationPRE, "boss_explosive_tell_PRE_animation_key");

	m_BossExplosiveTellAnimationPOST = setAnimation("Sprites/boss_explosive_attack_part2.png", 4, 500, 1300, 0.1f);
	AnimationCache::getInstance()->addAnimation(m_BossExplosiveTellAnimationPOST, "boss_explosive_tell_POST_animation_key");




	m_BossIdleAnimation = setAnimation("Sprites/boss_idle.png", 8 ,5, 500, 1300, 0.1f);
	AnimationCache::getInstance()->addAnimation(m_BossIdleAnimation, "boss_idle_animation_key");

}

//Animation setter, to store the animation frames in the animation cache to be called later
cocos2d::Animation* marcos::AnimationManager::setAnimation(const std::string a_String, const int a_NumFrames, const float a_Width, const float a_Height, const float a_Delay)
{
	cocos2d::Vector<cocos2d::SpriteFrame*> m_AnimFrames;

	for (int i = 0; i < a_NumFrames; i++)
	{
		auto frame = cocos2d::SpriteFrame::create(a_String, cocos2d::Rect(a_Width * i, 3, a_Width, a_Height));
		m_AnimFrames.pushBack(frame);
	}

	auto Animation = cocos2d::Animation::createWithSpriteFrames(m_AnimFrames, a_Delay);
	return Animation;

}

cocos2d::Animation* marcos::AnimationManager::setAnimation(const std::string a_String, const int a_RowFrames, const int a_rows, const float a_Width, const float a_Height, const float a_Delay)
{
	cocos2d::Vector<cocos2d::SpriteFrame*> m_AnimFrames;

	for (int i = 0; i < a_rows; i++)
	{
		for (int j = 0; j < a_RowFrames && j < 8; j++)
		{
			auto frame = cocos2d::SpriteFrame::create(a_String, cocos2d::Rect(a_Width * j, a_Height * i, a_Width, a_Height));
			m_AnimFrames.pushBack(frame);
		}
	}

	auto Animation = cocos2d::Animation::createWithSpriteFrames(m_AnimFrames, a_Delay);
	return Animation;

}