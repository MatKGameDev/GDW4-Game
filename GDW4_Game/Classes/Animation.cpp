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

cocos2d::Animation* marcos::AnimationManager::m_ProjectileAttackRightAnimation = new cocos2d::Animation();
cocos2d::Animation* marcos::AnimationManager::m_ProjectileAttackLeftAnimation = new cocos2d::Animation();

//Grappling
cocos2d::Animation* marcos::AnimationManager::m_GrapplingRightAnimation = new cocos2d::Animation();
cocos2d::Animation* marcos::AnimationManager::m_GrapplingLeftAnimation = new cocos2d::Animation();

cocos2d::Animation* marcos::AnimationManager::m_ShootingGrappleLeftAnimation = new cocos2d::Animation();
cocos2d::Animation* marcos::AnimationManager::m_ShootingGrappleRightAnimation = new cocos2d::Animation();

cocos2d::Animation* marcos::AnimationManager::m_GrappleJumpRightAnimation = new cocos2d::Animation();
cocos2d::Animation* marcos::AnimationManager::m_GrappleJumpLeftAnimation = new cocos2d::Animation();


//boss

cocos2d::Animation* marcos::AnimationManager::m_BossFlameAnimation = new cocos2d::Animation();
cocos2d::Animation* marcos::AnimationManager::m_BossFlameTellAnimation = new cocos2d::Animation();


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

	/////////////////////////////////////// A T T A C K I N G /////////////////////////////////////////
	m_MeleeAttackRightAnimation = setAnimation("Sprites/melee_right.png", 4, 177, 138, 0.1f);
	AnimationCache::getInstance()->addAnimation(m_MeleeAttackRightAnimation, "melee_right_animation_key");

	m_MeleeAttackLeftAnimation = setAnimation("Sprites/melee_left.png", 4, 177, 135, 0.1f);
	AnimationCache::getInstance()->addAnimation(m_MeleeAttackLeftAnimation, "melee_left_animation_key");


	m_ProjectileAttackRightAnimation = setAnimation("Sprites/projectile_right.png", 6, 105, 135, 0.1f);
	AnimationCache::getInstance()->addAnimation(m_ProjectileAttackRightAnimation, "projectile_right_animation_key");

	m_ProjectileAttackLeftAnimation = setAnimation("Sprites/projectile_left.png", 6, 105, 135, 0.1f);
	AnimationCache::getInstance()->addAnimation(m_ProjectileAttackLeftAnimation, "projectile_left_animation_key");

	/////////////////////////////////////// G R A P P L I N G /////////////////////////////////////////
	m_GrapplingRightAnimation = setAnimation("Sprites/grapple_right.png", 3, 105, 135, 0.06f);
	AnimationCache::getInstance()->addAnimation(m_GrapplingRightAnimation, "grapple_right_animation_key");

	m_GrapplingLeftAnimation = setAnimation("Sprites/grapple_left.png", 3, 105, 135, 0.06f);
	AnimationCache::getInstance()->addAnimation(m_GrapplingLeftAnimation, "grapple_left_animation_key");


	m_ShootingGrappleLeftAnimation = setAnimation("Sprites/shooting_grapple_right.png", 2, 120, 135, 0.1f);
	AnimationCache::getInstance()->addAnimation(m_ShootingGrappleLeftAnimation, "shooting_grapple_right_animation_key");

	m_ShootingGrappleRightAnimation = setAnimation("Sprites/shooting_grapple_left.png", 2, 120, 135, 0.1f);
	AnimationCache::getInstance()->addAnimation(m_ShootingGrappleRightAnimation, "shooting_grapple_left_animation_key");


	m_GrappleJumpRightAnimation = setAnimation("Sprites/grapple_jump_right.png", 6, 105, 135, 0.1f);
	AnimationCache::getInstance()->addAnimation(m_GrappleJumpRightAnimation, "grapple_jump_right_animation_key");

	m_GrappleJumpLeftAnimation = setAnimation("Sprites/grapple_jump_left.png", 6, 105, 135, 0.1f);
	AnimationCache::getInstance()->addAnimation(m_GrappleJumpLeftAnimation, "grapple_jump_left_animation_key");

	
	//////////////////////////////////////////// B O S S ///////////////////////////////////////////

	m_BossFlameTellAnimation = setAnimation("Sprites/boss_flamethrow.png", 27, 500, 1300, 0.1f);
	AnimationCache::getInstance()->addAnimation(m_BossFlameTellAnimation, "boss_flame_tell_animation_key");

	m_BossFlameAnimation = setAnimation("Sprites/flame.png", 8, 3, 1920, 500, 0.1f);
	AnimationCache::getInstance()->addAnimation(m_BossFlameAnimation, "boss_flame_animation_key");

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
		for (int j = 0; j < a_RowFrames || j < 8; j++)
		{
			auto frame = cocos2d::SpriteFrame::create(a_String, cocos2d::Rect(a_Width * j, a_Height * i, a_Width, a_Height));
			m_AnimFrames.pushBack(frame);
		}
	}

	auto Animation = cocos2d::Animation::createWithSpriteFrames(m_AnimFrames, a_Delay);
	return Animation;

}