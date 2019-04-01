#include "Boss.h"
#include "Hero.h"
#include "Boss/Ability States/BossIdleState.h"
#include "Boss/Attacks/Projectiles.h"
#include "VictoryScreen.h"
#include "GroundTile.h"


Boss::Boss(Hero* heroInstance, cocos2d::Scene* sceneForBoss, float height, float width)
	: sprite(cocos2d::Sprite::create()), bossScene(sceneForBoss), health(10)
{
	sprite->setPosition(230, 450);
	initHitbox();
	state = new Idling4FirstBoss(this);
}

Boss::~Boss()
{
	delete state;
}

void Boss::setState(FirstBossState* newState)
{
	if (state != nullptr)
		delete state;
	state = newState;
}

/**
 * @brief Set the index for the hitbox base on the
 * new state
 * @param newIndex The new enum for the index
 */
void Boss::setHitboxIndex(HitboxIndex newIndex)
{
	hitboxIndex = newIndex;
}

/**
 * @brief Get the boss health
 * @return Return int
 */
int Boss::getHealth() const
{
	return health;
}

/**
 * @brief Get the boss sprite
 * @return Return the cocos2d::Sprite pointer
 */
cocos2d::Sprite* Boss::getSprite() const
{
	return sprite;
}

/**
 * @brief Get the vector of lavaList
 * @return Return vector<Boss1LavaAttack*>
 */
std::vector<Boss1LavaAttack*> Boss::getLavaList() const
{
	return lavaList;
}

/**
 * @brief Return the scene that the boss is on
 * @return Return cocos2d::Scene pointer
 */
cocos2d::Scene* Boss::getBossScene() const
{
	return bossScene;
}

/**
 * @brief Returns vector of hitboxes
 * @return Return vector<Hitbox*>
 */
std::vector<HitBox*> Boss::getHitBox() const
{
	return hitBoxLists[hitboxIndex];
}

/**
 * @brief Reduce both health due to hero's attack
 */
void Boss::takeDamage()
{
	sprite->setVisible(false); //flicker sprite upon taking damage
	health--;

	if (health == 0)
		cocos2d::Director::getInstance()->replaceScene(TransitionFade::create(2.0f, VictoryScreen::createScene(), Color3B(0, 0, 0)));
}

/**
 * @brief Gets the boss's current state
 * @return Return FirstBossState pointer
 */
FirstBossState* Boss::getCurrentState() const
{
	return state;
}

/**
 * @brief Updates the boss and all lava attacks from
 * the boss
 * @param deltaT The time changes from last frame to current frame
 */
void Boss::update(const float &deltaT)
{
	state->update(deltaT);

	for (auto attack : lavaList)
	{
		//Update the position of the attack
		attack->update(deltaT);

		//Check if the attack hits the ground tile
		for (auto ground : GroundTile::groundTileList)
		{
			if (attack->getHitBox().intersectsRect(ground->hitBox))
			{
				attack->hitByEnvironment();
				break;
			}
		}
	}

	//make sure sprite is visible
	sprite->setVisible(true);
}

/**
 * @brief Creates lava balls
 */
void Boss::spewLava()
{
	for (size_t i = 1; i <= 3; i++)
	{
		lavaList.push_back(new LavaBall(i, this));
	}
}

/**
 * @brief Creates a flame thrower
 */
void Boss::activateFlameThrower()
{
	lavaList.push_back(new FlameThrower(this));
}

/**
 * @brief Creates an explosive bullet
 */
void Boss::shootExplosiveBullet()
{
	lavaList.push_back(new ExplosiveBullet(Hero::hero->sprite->getPosition(), this));
}

/**
 * @brief Remove a lava attack from the lavaList
 * @param attackToRemove The attack to be removed
 */
void Boss::removeFromLavaList(Boss1LavaAttack* attackToRemove)
{
	for (size_t i = 0; i < lavaList.size(); i++)
	{
		if (lavaList[i] == attackToRemove)
			lavaList.erase(lavaList.begin() + i);
	}
}

/**
 * @brief Adds a lava attack to the lavaList
 * @param attackToAdd The attack to be added to the list
 */
void Boss::addAttack(Boss1LavaAttack* attackToAdd)
{
	lavaList.push_back(attackToAdd);
}

/**
 * @brief Initialize all the hitboxes for all different states
 */
void Boss::initHitbox()
{
	hitBoxLists.push_back(initIdleHitbox());
	hitBoxLists.push_back(initFlameSplitHitbox());
	hitBoxLists.push_back(initFlameThrowerHitbox());
}

/**
 * @brief This function initialize hitboxes for idling.
 * Explosive bullet state also share the same hitboxes
 * @return Returns a Hitbox pointer vector
 */
std::vector<HitBox*> Boss::initIdleHitbox() const
{
	std::vector<HitBox*> tempVector;
	tempVector.push_back(new HitBox(Vec2(175, 845), 100, 350));
	tempVector.push_back(new HitBox(Vec2(350, 790), 90, 100));
	tempVector.push_back(new HitBox(Vec2(395, 575), 350, 75));
	tempVector.push_back(new HitBox(Vec2(340, 300), 175, 100));
	return tempVector;
}

/**
 * @brief This function initialize hitboxes for flame split
 * @return Returns a Hitbox pointer vector
 */
std::vector<HitBox*> Boss::initFlameSplitHitbox() const
{
	std::vector<HitBox*> tempVector;
	tempVector.push_back(new HitBox(Vec2(175, 875), 100, 350));
	tempVector.push_back(new HitBox(Vec2(350, 820), 90, 100));
	tempVector.push_back(new HitBox(Vec2(395, 605), 350, 75));
	tempVector.push_back(new HitBox(Vec2(340, 210), 175, 100));
	return tempVector;
}

/**
 * @brief This function initialize hitboxes for flame thrower
 * @return Returns a Hitbox pointer vector
 */
std::vector<HitBox*> Boss::initFlameThrowerHitbox() const
{
	std::vector<HitBox*> tempVector;
	tempVector.push_back(new HitBox(Vec2(175, 945), 100, 350));
	tempVector.push_back(new HitBox(Vec2(350, 890), 90, 100));
	tempVector.push_back(new HitBox(Vec2(395, 675), 350, 75));
	tempVector.push_back(new HitBox(Vec2(340, 125), 175, 100));
	return tempVector;
}