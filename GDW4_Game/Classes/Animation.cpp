#include "Animation.h"

//static variable initialization
cocos2d::Animation* marcos::AnimationManager::m_IdlingLeftAnimation = new cocos2d::Animation();
cocos2d::Animation* marcos::AnimationManager::m_IdlingRightAnimation = new cocos2d::Animation();

cocos2d::Action* marcos::AnimationManager::m_IdleActionAnimation = new cocos2d::Action();

cocos2d::Animation* marcos::AnimationManager::m_RunningRightAnimation = new cocos2d::Animation();
cocos2d::Animation* marcos::AnimationManager::m_RunningLeftAnimation = new cocos2d::Animation();


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

	m_IdlingRightAnimation = setAnimation("Sprites/idle_right.png", 21, 75, 135, 0.2f);
	AnimationCache::getInstance()->addAnimation(m_IdlingRightAnimation, "idle_right_animation_key");

	m_IdlingLeftAnimation = setAnimation("Sprites/idle_right.png", 21, 75, 135, 0.2f);
	AnimationCache::getInstance()->addAnimation(m_IdlingLeftAnimation, "idle_left_animation_key");


	m_RunningRightAnimation = setAnimation("Sprites/running_right.png", 6, 105, 135, 0.1f);
	AnimationCache::getInstance()->addAnimation(m_RunningRightAnimation, "running_right_animation_key");


	m_RunningLeftAnimation = setAnimation("Sprites/running_left.png", 6, 105, 135, 0.1f);
	AnimationCache::getInstance()->addAnimation(m_RunningLeftAnimation, "running_left_animation_key");

}

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