#include "Animation.h"

//static variable initialization


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//																																			  //
//															Animation Class																	  //
//																																			  //
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//default constructor initializes things to 0
marcos::Animation::Animation()
{
	m_NumFrames = 0;
	m_Width = 0;
	m_Height = 0;
	m_Delay = 0.2f;
	
}
//Constructor initializes 
marcos::Animation::Animation(int a_NumFrames, float a_Width, float a_Height, float a_Delay, cocos2d::Sprite * a_Sprite, std::string a_Name): 
	m_NumFrames(a_NumFrames),
	m_Width(a_Width),
	m_Height(a_Height),
	m_Delay(a_Delay),
	m_Sprite(a_Sprite)
{
	setAnimation(a_Name);
}

//destructor clears memory
marcos::Animation::~Animation()
{
	//m_Sprite->release();
	//m_Animate->release();
	//m_Animation->release();
}

//initializing animation class members
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

//running the animation -> extend to this from class with animation object
void marcos::Animation::runAnimation()
{
	m_Sprite->runAction(cocos2d::RepeatForever::create(m_Animate));
}

//setting number of frames for base class
void marcos::Animation::setNumFrames(int a_frames)
{
	m_NumFrames = a_frames;
}

//setting width for base class
void marcos::Animation::setWidth(float a_Width)
{
	m_Width = a_Width;
}

//setting height for base class
void marcos::Animation::setHeight(float a_Height)
{
	m_Height = a_Height;
}

//setting delay for base class
void marcos::Animation::setDelay(float a_Delay)
{
	m_Delay = a_Delay;
}

//setting sprite for base class
void marcos::Animation::setSprite(cocos2d::Sprite *a_Sprite)
{
	m_Sprite = a_Sprite;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//																																			  //
//															HeroAnimaiton Class																  //
//																																			  //
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



marcos::HeroAnimation::HeroAnimation(cocos2d::Sprite * a_Sprite):
	m_AttackingAnimation(a_Sprite),
	m_LandingAnimation(a_Sprite),
	m_JumpingAnimation(a_Sprite),
	m_IdlingAnimation(a_Sprite),
	m_RunningAnimation(a_Sprite),
	m_GrapplingAnimation(a_Sprite)
{

	m_HeroAnimation = new Animation(4, 120, 135, 0.2f, a_Sprite, "Sprites/Running_Spritesheet1.png");
	m_Sprite = a_Sprite;
}

cocos2d::Sprite * marcos::HeroAnimation::getSprite()
{
	return this->m_Sprite;
}

void marcos::HeroAnimation::runAnimation()
{
	this->getSprite()->runAction(cocos2d::RepeatForever::create(m_HeroAnimation->m_Animate));
}



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//																																			  //
//															Hero Animations																	  //
//																																			  //
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////// A T T A C K ///////////////////////////////////////////////////////
marcos::AttackingAnimation::AttackingAnimation(cocos2d::Sprite* a_Sprite)
{
	m_AttackAnimation = Animation(4, 120, 135, 0.2f, a_Sprite, "Sprites/Running_Spritesheet1.png");
}









/////////////////////////////////////////////////// G R A P P L E ///////////////////////////////////////////////////////
marcos::GrapplingAnimation::GrapplingAnimation(cocos2d::Sprite* a_Sprite)
{
	m_GrappleAnimation =  Animation(4, 120, 135, 0.2f, a_Sprite, "Sprites/Running_Spritesheet1.png");
}









////////////////////////////////////////////////// L A N D I N G ////////////////////////////////////////////////////////
marcos::LandingAnimation::LandingAnimation(cocos2d::Sprite* a_Sprite)
{
	m_LandAnimation =  Animation(4, 120, 135, 0.2f, a_Sprite, "Sprites/Running_Spritesheet1.png");
}









/////////////////////////////////////////////////// I D L I N G /////////////////////////////////////////////////////////
marcos::IdlingAnimation::IdlingAnimation(cocos2d::Sprite* a_Sprite)
{
	m_IdleAnimation =  Animation(4, 120, 135, 0.2f, a_Sprite, "Sprites/Running_Spritesheet1.png");
}








////////////////////////////////////////////////// R U N N I N G ////////////////////////////////////////////////////////
marcos::RunningAnimation::RunningAnimation(cocos2d::Sprite* a_Sprite)
{
	m_MoveAnimation =  Animation(4, 120, 135, 0.2f, a_Sprite, "Sprites/Running_Spritesheet1.png");
}








////////////////////////////////////////////////// J U M P I N G ////////////////////////////////////////////////////////
marcos::JumpingAnimation::JumpingAnimation(cocos2d::Sprite* a_Sprite)
{
	m_JumpAnimation =  Animation(4, 120, 135, 0.2f, a_Sprite, "Sprites/Running_Spritesheet1.png");
}