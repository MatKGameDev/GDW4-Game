#include "Boss1Attack.h"
#include <cmath>
#include <base/CCDirector.h>
#include "Boss.h"

Boss1LavaAttack::Boss1LavaAttack(Boss* bossInstance) : bossPointer(bossInstance)
{
}



LavaBall::LavaBall(const cocos2d::Vec2& heroPosition, Boss *bossInstance)
	: ballSprite(cocos2d::Sprite::create("LavaBall.png")), gravity(cocos2d::Vec2(0, -500)), position(bossInstance->getMouthPosition()), Boss1LavaAttack(bossInstance)
{
	//Set Position for the lava ball
	ballSprite->setPosition(bossInstance->getMouthPosition());
	cocos2d::Director::getInstance()->getRunningScene()->addChild(ballSprite);

	const float initVelocity{ 700 };
	const float thetaInRadian = calculateAngle(heroPosition, bossInstance->getMouthPosition(), initVelocity);

	velocity.x = initVelocity * cos(thetaInRadian);
	velocity.y = initVelocity * sin(thetaInRadian);

}

LavaBall::~LavaBall()
{
	ballSprite->release();
}

void LavaBall::update(const float& deltaT)
{
	//Update normally
	velocity.y += gravity.y * deltaT;
	//Velocity_x is constant
	position.x += velocity.x*deltaT;
	position.y += velocity.y *deltaT;

	//Velocity_y += acceleration * deltaT

	//Position update like normal Or position_y += gravity*(deltaT)^2
	ballSprite->setPosition(position);
}

/*
 * This function calculates the angle to shoot the projectile to hit the hero
 */
float LavaBall::calculateAngle(const cocos2d::Vec2& heroPosition, const cocos2d::Vec2& bossMouthPosition, const float &velocity) const
{
	//Calculate the Displacement_y and Displacement_x
	const cocos2d::Vec2 displacementFromMouthToHero = heroPosition - bossMouthPosition;

	//Variables for quadratic formula
	const float a = (gravity.y * pow(displacementFromMouthToHero.x, 2)) / (2 * pow(velocity, 2));
	const float b = displacementFromMouthToHero.x;
	const float c = a - displacementFromMouthToHero.y;

	/*tan(theta) = quadratic formula of variables above
	 *(link: https://cdn.kastatic.org/googleusercontent/nI2riiPBcl9hZ22KKdYZGFmsVNhcKLiuwPly9l1tU5BMaqcOs9bfPKRyoGAFgK-PNpc-c7x_tNuskGdzawvy_Pza) */
	const float additionNumerator = -b + sqrt(pow(b, 2) - 4 * a*c);
	const float subtractionNumerator = -b - sqrt(pow(b, 2) - 4 * a*c);
	const float denominator = 2 * a;

	//tan(theta) has 2 answer
	const float firstTheta = atan(additionNumerator / denominator);
	const float secondTheta = atan(subtractionNumerator / denominator);

	//The angle for projectile motion must be between 0 < theta < 90
	if (firstTheta < 0 || firstTheta > M_PI_2)
		return secondTheta;
	if (secondTheta < 0 || secondTheta > M_PI_2)
		return firstTheta;

	//Return the larger angle if both are in range
	if (firstTheta > secondTheta)
		return firstTheta;
	if (secondTheta > firstTheta)
		return secondTheta;

	//Throw if no condition for angle is met
	throw;
}


FlameThrower::FlameThrower(Boss *bossInstance) : Boss1LavaAttack(bossInstance), onTime(1.0f), drawNode(cocos2d::DrawNode::create())
{
	drawNode->drawRect(bossInstance->getMouthPosition(), cocos2d::Vec2(bossInstance->getMouthPosition().x + 1920, bossInstance->getMouthPosition().y + 100), cocos2d::Color4F(0.0f, 1.0f, 0.0f, 1.0f));
	cocos2d::Director::getInstance()->getRunningScene()->addChild(drawNode);
}

FlameThrower::~FlameThrower()
{
	bossPointer->removeFromLavaList(this);
	cocos2d::Director::getInstance()->getRunningScene()->removeChild(drawNode);
}

void FlameThrower::update(const float& deltaT)
{
	onTime -= deltaT;
	if (onTime <= 0)
		delete this;
}

SuckerBullet::SuckerBullet(const cocos2d::Vec2& heroLocation, Boss* bossInstance) : Boss1LavaAttack(bossInstance), bulletSprite(cocos2d::Sprite::create("LavaBall.png")), currentPosition(bossInstance->getMouthPosition())
{
	//Set up the sprite
	bulletSprite->setPosition(bossInstance->getMouthPosition());
	cocos2d::Director::getInstance()->getRunningScene()->addChild(bulletSprite);

	//set up the physics
	cocos2d::Vec2 tempVector = heroLocation - bossInstance->getMouthPosition();
	lengthVector = tempVector.getLength();
	bulletVelocity = tempVector.getNormalized() * 600;

	this->heroLocation = heroLocation;
}

SuckerBullet::~SuckerBullet()
{
	bossPointer->removeFromLavaList(this);
	cocos2d::Director::getInstance()->getRunningScene()->removeChild(bulletSprite);
}

void SuckerBullet::update(const float& deltaT)
{
	lastPosition = currentPosition;
	currentPosition += bulletVelocity * deltaT;

	bulletSprite->setPosition(currentPosition);

	traveledLength += (lastPosition - currentPosition).getLength();
	if (lengthVector <= traveledLength)
	{
		delete this;
	}
}
