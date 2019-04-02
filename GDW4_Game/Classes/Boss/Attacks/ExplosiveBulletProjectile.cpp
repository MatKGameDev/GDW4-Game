#include "Boss/Attacks/ExplosiveBulletProjectile.h"
#include "Boss/General/Boss.h"
#include "Hero.h"

/**
 * @brief Initialize data members for explosive area and set up sprite animation
 *
 * @param startPosition The position where the explosive bullet was destroyed
 * @param bossInstance The current bossPointer
 */
ExplosiveArea::ExplosiveArea(const cocos2d::Vec2& startPosition, Boss* bossInstance)
	: Boss1LavaAttack(bossInstance, "Sprites/spit_sprite.png"), appliedForce(false),
	constantG(7500)
{
	//Set up the sprite's information
	position = startPosition;
	sprite->setPosition(position);
	attackType = BossAttack::ExplosiveBullet;

	//Set up hitbox
	hitBox = new HitBox(position, 120, 120);

	//Get the animation
	const auto animation = marcos::AnimationManager::getAnimation("boss_explosive_POST_animation_key");

	//Run action
	sprite->runAction
	(
		cocos2d::Sequence::create
		(
			cocos2d::Repeat::create(animation, 1),
			cocos2d::CallFunc::create([&] {delete this; }),
			nullptr
		)
	);
}

/**
 * @brief Run the destruction for explosive area object. This will
 * also set the hero's position to 0
 */
ExplosiveArea::~ExplosiveArea()
{
	resetHeroForce();
	bossPointer->removeFromLavaList(this);
}

/**
 * @brief This function updates the hitbox, as well as
 * add force to the player
 */
void ExplosiveArea::update(const float& deltaT)
{
	hitBox->updateHitBox(position);
	addForceToHero();
}

/**
 * @brief This function adds a force to the hero if they are in range
 * and reset it to zero if they are not;
 */
void ExplosiveArea::addForceToHero() const
{
	//Apply force to hero if the hero position is in range AND
	if (isHeroInRange())
		Hero::hero->force = calculateDirectionToHero() * constantG;
	else
		resetHeroForce();
	
}

/**
 * @brief This function calculate the direction from the hero
 * to the center of the explosive area
 *
 * @return Returns Vect2 class
 */
Vect2 ExplosiveArea::calculateDirectionToHero() const
{
	return Vect2(position.x - Hero::hero->getPosition().x, position.y - Hero::hero->getPosition().y).getNormalized();
}

/**
 * @brief This function resets the hero's force if the explosive
 * area has applied a force to the hero
 */
void ExplosiveArea::resetHeroForce() const
{
	Hero::hero->force = Vect2(0, 0);
}

/**
 * @brief This function checks if the hero is in the effective range
 * @return True if hero is in range.\n False if hero is not in range
 */
bool ExplosiveArea::isHeroInRange() const
{
	return true;
	return Vec2(Hero::hero->getPosition().x - position.x, Hero::hero->getPosition().y - position.y).getLength() 
	< 300;
}

/**
 * @brief Calculate distance square between the hero's position and  the 
 * explosive area position
 * @return Return distance square as float
 */
float ExplosiveArea::calculateDistanceSquare() const
{
	return Vec2(Hero::hero->getPosition().x - position.x, Hero::hero->getPosition().y - position.y).getLength();
}

//Explosive Bullet static members
const float ExplosiveBullet::accelerationMultiplier = 2000;
const float ExplosiveBullet::velocityMultiplier = 1250;

/**
 *@brief This initialize the data members and sprite action for the explosive bullet
 */
ExplosiveBullet::ExplosiveBullet(const cocos2d::Vec2& heroLocation, Boss* bossInstance)
	: Boss1LavaAttack(bossInstance, "Sprites/spit_sprite.png")
{
	//Set up the sprite
	position.set(300, 300);
	sprite->setPosition(position);

	//Set up the animation
	const auto animation = marcos::AnimationManager::getAnimation("boss_explosive_PRE_animation_key");

	//Run actions
	sprite->runAction
	(
		cocos2d::Sequence::create
		(
			cocos2d::Repeat::create(animation->clone(), 1),
			cocos2d::CallFunc::create([&] {setUpPhysic(heroLocation); isWaiting = false; }),
			nullptr
		)
	);

	//Set up hit box
	hitBox = new HitBox(position, 50, 50);
}

ExplosiveBullet::~ExplosiveBullet()
{
	bossPointer->removeFromLavaList(this);
	bossPointer->addAttack(new ExplosiveArea(position, bossPointer));
}

/**
 * @brief Updates the physics for the object
 * @param deltaT The changes in time from the last frame to the
 * current frame
 */
void ExplosiveBullet::update(const float& deltaT)
{
	if (!isWaiting)
	{
		//physics update
		velocity += acceleration * deltaT;
		position += velocity * deltaT;

		////Update the sprite
		sprite->setPosition(position);
		hitBox->updateHitBox(position);
	}
}

/**
 * @brief This will delete the explosive bullet
 */
void ExplosiveBullet::hitByHero()
{
	delete this;
}

/**
 * @brief This will delete the explosive bullet
 */
void ExplosiveBullet::hitByEnvironment()
{
	delete this;
}

/**
 * @brief This will calculate all the initial physics
 * components
 * @param heroPos The hero location
 */
void ExplosiveBullet::setUpPhysic(const cocos2d::Vec2& heroPos)
{
	const cocos2d::Vec2 tempVector = heroPos - position;
	acceleration = tempVector.getNormalized() * accelerationMultiplier;
	velocity = tempVector.getNormalized() * velocityMultiplier;
}
