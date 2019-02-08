#include "Animation.h"

//Animation Base Class

marcos::Animation::Animation()
{
	m_NumFrames = 0;
	m_Width = 0;
	m_Height = 0;
	m_Delay = 0.2f;
	
}

marcos::Animation::Animation(int a_NumFrames, float a_Width, float a_Height, float a_Delay, cocos2d::Sprite * a_Sprite, std::string a_Name): 
	m_NumFrames(a_NumFrames),
	m_Width(a_Width),
	m_Height(a_Height),
	m_Delay(a_Delay),
	m_Sprite(a_Sprite)
{
	setAnimation(a_Name);
}

marcos::Animation::~Animation()
{
	//m_Sprite->release();
	//m_Animate->release();
	//m_Animation->release();
}

void marcos::Animation::setAnimation(std::string a_String)
{
	for (int i = 0; i < m_NumFrames; i++)
	{
		auto frame = cocos2d::SpriteFrame::create(a_String, cocos2d::Rect(m_Width * i, 3, m_Width, m_Height));
		m_AnimFrames.pushBack(frame);
	}

	m_Animation = cocos2d::Animation::createWithSpriteFrames(m_AnimFrames, m_Delay);
	m_Animate = cocos2d::Animate::create(m_Animation);

}
void marcos::Animation::runAnimation()
{
	m_Sprite->runAction(cocos2d::RepeatForever::create(m_Animate));
}

void marcos::Animation::setNumFrames(int a_frames)
{
	m_NumFrames = a_frames;
}

void marcos::Animation::setWidth(float a_Width)
{
	m_Width = a_Width;
}

void marcos::Animation::setHeight(float a_Height)
{
	m_Height = a_Height;
}

void marcos::Animation::setDelay(float a_Delay)
{
	m_Delay = a_Delay;
}

void marcos::Animation::setSprite(cocos2d::Sprite *a_Sprite)
{
	m_Sprite = a_Sprite;
}

//Animation Child Clases