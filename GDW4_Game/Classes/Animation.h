#pragma once
#ifndef ANIMATION_H
#define ANIMATION_H
#include "cocos2d.h"
using namespace cocos2d;

//#include "GameObject.h"

namespace marcos
{
	class AnimationManager
	{
	public:
		//Member function
		static void init();
		static cocos2d::Animate* getAnimation(const std::string& animationKey);
		static cocos2d::Animate* getAnimationWithAnimationTime(const std::string& animationKey, const float &animationTime);


	private:

		static void addAnimation(const std::string fileName, const int a_NumFrames, const float a_Width, const float a_Height, 
			const std::string& keyName, const float a_Delay = 0.1f);
		static void addAnimation(const std::string fileName, const int a_RowFrames, const int a_rows, const float a_Width, const float a_Height,
			const std::string& keyName, const float a_Delay = 0.1f);
		static void addAnimation(Animation* animationToAdd, const std::string& animationKey);

		//Private animation init functions
		static void initBossStateAnimation();
		static void initBossAttackParticleAnimation();
	};
}
#endif