#pragma once
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

		static cocos2d::Animation* m_JumpingAnimation;
		static cocos2d::Animation* m_LandingAnimation;


		static cocos2d::Animation* m_RunningRightAnimation;
		static cocos2d::Animation* m_RunningLeftAnimation;

		static cocos2d::Animation* m_IdlingRightAnimation;
		static cocos2d::Animation* m_IdlingLeftAnimation;

		static cocos2d::Animation* m_AttackingAnimation;
		static cocos2d::Animation* m_GrapplingAnimation;

		static cocos2d::Action* m_IdleActionAnimation;


	private:


	};
}