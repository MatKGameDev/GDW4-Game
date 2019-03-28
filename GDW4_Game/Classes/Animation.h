#pragma once
#ifndef ANIMATION_H
#define ANIMATION_H

#include "GameObject.h"

namespace marcos
{
	class AnimationManager
	{
	public:

		AnimationManager();
		~AnimationManager();


		static void init();

		static cocos2d::Animation* setAnimation(const std::string a_String, const int a_NumFrames, const float a_Width, const float a_Height, const float a_Delay);

		static cocos2d::Animation * setAnimation(const std::string a_String, const int a_NumFrames, const int a_rows, const float a_Width, const float a_Height, const float a_Delay);


		//idling
		static cocos2d::Animation* m_IdlingRightAnimation;
		static cocos2d::Animation* m_IdlingLeftAnimation;

		//jumping
		static cocos2d::Animation* m_JumpingRightAnimation;
		static cocos2d::Animation* m_JumpingLeftAnimation;

		static cocos2d::Animation* m_FallingRightAnimation;
		static cocos2d::Animation* m_FallingLeftAnimation;

		//running
		static cocos2d::Animation* m_RunningRightAnimation;
		static cocos2d::Animation* m_RunningLeftAnimation;

		//attacking
		static cocos2d::Animation* m_MeleeAttackRightAnimation;
		static cocos2d::Animation* m_MeleeAttackLeftAnimation;

		static cocos2d::Animation* m_MeleeAttackUpRightAnimation;
		static cocos2d::Animation* m_MeleeAttackUpLeftAnimation;


		//grappling
		static cocos2d::Animation* m_GrapplingRightAnimation;
		static cocos2d::Animation* m_GrapplingLeftAnimation;

		static cocos2d::Animation* m_ShootingGrappleRightAnimation;
		static cocos2d::Animation* m_ShootingGrappleLeftAnimation;
		

		static cocos2d::Animation* m_GrappleJumpRightAnimation;
		static cocos2d::Animation* m_GrappleJumpLeftAnimation;


		static cocos2d::Animation* m_GrappleHoldRightAnimation;
		static cocos2d::Animation* m_GrappleHoldLeftAnimation;

		//boss
		static cocos2d::Animation* m_BossFlameAnimation;
		static cocos2d::Animation* m_BossFlameTellAnimationPRE;
		static cocos2d::Animation* m_BossFlameTellAnimationPOST;

		static cocos2d::Animation* m_BossSpitAnimation;
		static cocos2d::Animation* m_BossSpitTellAnimationPRE;
		static cocos2d::Animation* m_BossSpitTellAnimationPOST;

		static cocos2d::Animation* m_BossExplosiveTellAnimationPRE;
		static cocos2d::Animation* m_BossExplosiveTellAnimationPOST;

		static cocos2d::Animation* m_BossExplosionAnimationPRE;
		static cocos2d::Animation* m_BossExplosionAnimationPOST;


		static cocos2d::Animation* m_BossIdleAnimation;



	private:


	};
}
#endif