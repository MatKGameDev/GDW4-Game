#include "Boss.h"
#include "Hero.h"
#include "Boss/Ability States/BossIdleState.h"

Boss::Boss(Hero* heroInstance, cocos2d::Scene* sceneForBoss, float height, float width)
	: bossSprite(cocos2d::Sprite::create("Sprites/boss.png")), mouthPosition(100, 500), bossScene(sceneForBoss),
	hitBox(sceneForBoss, height, width), heroPointer(heroInstance), health(10)
{
	bossSprite->setPosition(230, 450);
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

cocos2d::Vec2 Boss::getMouthPosition() const
{
	return mouthPosition;
}

cocos2d::Scene* Boss::getBossScene() const
{
	return bossScene;
}

cocos2d::Rect Boss::getHitBox() const
{
	return hitBox.hitBox;
}

void Boss::takeDamage()
{
	bossSprite->setVisible(false); //flicker sprite upon taking damage
	health--;
}

FirstBossState* Boss::getCurrentState() const
{
	return state;
}

void Boss::update(const float &deltaT, const cocos2d::Vec2 &heroPosition)
{
	state->update(deltaT);
	hitBox.updateHitBox(bossSprite->getPosition());

	for (size_t i = 0; i < lavaList.size(); i++)
	{
		try {
			lavaList[i]->update(deltaT);
		}
		catch (...)
		{
			lavaList.erase(lavaList.begin() + i);
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

void Boss::shootSucker()
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
