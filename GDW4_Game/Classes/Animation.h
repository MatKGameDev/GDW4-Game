#pragma once
#include "cocos2d.h"
namespace marcos
{
	class Animation
	{

	public:

		Animation();
		Animation(int a_NumFrames, float a_Width, float a_Height, float a_Delay, cocos2d::Sprite *a_Sprite, std::string a_Name);
		~Animation();


		void setAnimation(std::string a_String);

		void runAnimation();
		void setNumFrames(int a_frames);
		void setWidth(float a_Width);
		void setHeight(float a_Height);
		void setDelay(float a_Delay);
		void setSprite(cocos2d::Sprite *a_Sprite);

		cocos2d::Sprite *m_Sprite;

		int m_NumFrames;
		float m_Width;
		float m_Height;
		float m_Delay;
		cocos2d::Animation *m_Animation;
		cocos2d::Animate *m_Animate;
		cocos2d::Vector<cocos2d::SpriteFrame*> m_AnimFrames;

	private:
	};


	class BossAnimation
	{
	public:
	
	private:
	};

	class IdlingAnimation 
	{
	public:
		IdlingAnimation(cocos2d::Sprite* a_Sprite);
		marcos::Animation m_IdleAnimation;
		cocos2d::Sprite* m_Sprite;
		void runAnimation();
	private:

	};

	class LandingAnimation
	{
	public:
		LandingAnimation(cocos2d::Sprite* a_Sprite);
		marcos::Animation m_LandAnimation;
	private:

	};

	class RunningAnimation 
	{

	public:
		RunningAnimation(cocos2d::Sprite* a_Sprite);
		void runAnimation();
		marcos::Animation m_MoveAnimation;
		cocos2d::Sprite* m_Sprite;

	private:

	};

	class GrapplingAnimation 
	{
	public:
		GrapplingAnimation(cocos2d::Sprite* a_Sprite);
		marcos::Animation m_GrappleAnimation;
	private:

	};

	class AttackingAnimation 
	{

	public:
		AttackingAnimation(cocos2d::Sprite* a_Sprite);
		marcos::Animation m_AttackAnimation;

	private:
		//placeholder int attackType;
		//placeholder int direction;

	};

	class JumpingAnimation 
	{

	public:
		JumpingAnimation(cocos2d::Sprite* a_Sprite);
		marcos::Animation m_JumpAnimation;
	private:

	};

	class HeroAnimation
	{

	public:
		HeroAnimation(cocos2d::Sprite* a_Sprite);
		cocos2d::Sprite* getSprite();
		cocos2d::Sprite* m_Sprite;
		void runAnimation();

		marcos::Animation *m_HeroAnimation;

		JumpingAnimation m_JumpingAnimation;
		LandingAnimation m_LandingAnimation;
		RunningAnimation m_RunningAnimation;
		AttackingAnimation m_AttackingAnimation;
		GrapplingAnimation m_GrapplingAnimation;
		IdlingAnimation m_IdlingAnimation;

	private:


	};
}