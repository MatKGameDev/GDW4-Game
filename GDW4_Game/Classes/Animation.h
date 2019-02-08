#pragma once
#include "cocos2d.h"
namespace marcos
{
	class Animation
	{

	public:

		Animation();
		Animation(int a_NumFrames, float a_Width, float a_Height, float a_Delay, cocos2d::Sprite *a_Sprite, std::string a_Name);
		Animation(std::string a_Name);
		~Animation();


		void setAnimation(std::string a_String);

		void runAnimation();
		void setNumFrames(int a_frames);
		void setWidth(float a_Width);
		void setHeight(float a_Height);
		void setDelay(float a_Delay);
		void setSprite(cocos2d::Sprite *a_Sprite);


	private:
		int m_NumFrames;
		float m_Width;
		float m_Height;
		float m_Delay;
		cocos2d::Animation *m_Animation;
		cocos2d::Animate *m_Animate;
		cocos2d::Sprite *m_Sprite;
		cocos2d::Vector<cocos2d::SpriteFrame*> m_AnimFrames;
	};

	class RunningAnimation : public Animation
	{

	public:
		RunningAnimation();

	private:

	};

	class AttackingAnimation : public Animation
	{

	public:
		AttackingAnimation();

	private:
		//placeholder int attackType;
		//placeholder int direction;

	};

	class JumpingAnimation : public Animation
	{

	public:
		JumpingAnimation();

	private:

	};

}