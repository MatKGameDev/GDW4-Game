#include "Boss.h"
#include "Hero.h"
#include "Boss/Ability States/BossIdleState.h"
#include "Boss/Attacks/Projectiles.h"
#include "VictoryScreen.h"
#include "GroundTile.h"


Boss::Boss(Hero* heroInstance, cocos2d::Scene* sceneForBoss, float height, float width)
	: bossSprite(cocos2d::Sprite::create("Sprites/boss.png")), bossScene(sceneForBoss),
	heroPointer(heroInstance), health(10)
{
	bossSprite->setPosition(230, 450);
	hitBox = new HitBox(bossSprite->getPosition(), height, width, bossScene);
	state = new Idling4FirstBoss(this);
}

Boss::~Boss()
{
	delete state;
	delete hitBox;
}

void Boss::setState(FirstBossState* newState)
{
	if (state != nullptr)
		delete state;
	state = newState;
}

int Boss::getHealth() const
{
	return health;
}

cocos2d::Sprite* Boss::getSprite() const
{
	return bossSprite;
}

std::vector<Boss1LavaAttack*> Boss::getLavaList() const
{
	return lavaList;
}

cocos2d::Scene* Boss::getBossScene() const
{
	return bossScene;
}

cocos2d::Rect Boss::getHitBox() const
{
	return hitBox->hitBox;
}

void Boss::takeDamage()
{
	bossSprite->setVisible(false); //flicker sprite upon taking damage
	health--;

	if (health == 0)
		cocos2d::Director::getInstance()->replaceScene(TransitionFade::create(2.0f, VictoryScreen::createScene(), Color3B(0, 0, 0)));
}

FirstBossState* Boss::getCurrentState() const
{
	return state;
}

void Boss::update(const float &deltaT)
{
	state->update(deltaT);
	hitBox->updateHitBox(bossSprite->getPosition());

	for (auto attack : lavaList) 
	{
		//Update the position of the attack
		attack->update(deltaT);

		//Check if the attack hits the ground tile
		for (auto ground: GroundTile::groundTileList)
		{
			if (attack->getHitBox().intersectsRect(ground->hitBox))
			{
				attack->hitByEnvironment();
				break;
			}
		}
	}

	//make sure sprite is visible
	bossSprite->setVisible(true);
}

void Boss::spewLava()
{
	for (size_t i = 1; i <= 3; i++)
	{
		lavaList.push_back(new LavaBall(i, this));
	}
}

void Boss::activateFlameThrower()
{
	lavaList.push_back(new FlameThrower(this));
}

void Boss::shootExplosiveBullet()
{
	lavaList.push_back(new ExplosiveBullet(heroPointer->sprite->getPosition(), this));
}

void Boss::removeFromLavaList(Boss1LavaAttack* elementToRemove)
{
	for (size_t i = 0; i < lavaList.size(); i++)
	{
		if (lavaList[i] == elementToRemove)
			lavaList.erase(lavaList.begin() + i);
	}
}

void Boss::addAttack(Boss1LavaAttack* attackToAdd)
{
	lavaList.push_back(attackToAdd);
}
