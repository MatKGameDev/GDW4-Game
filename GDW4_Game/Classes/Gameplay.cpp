#include "Gameplay.h"
#include "PauseMenu.h"
#include <iostream>
#include "HeroStateManager.h"
#include "Boss/General/Boss.h"
#include "XinputManager.h"
#include "DeathScreen.h"
#include "VictoryScreen.h"
#include "Boss/Attacks/Projectiles.h"
#include "Input Handler/InputHandler.h"

cocos2d::Scene* Gameplay::createScene()
{
	Scene* scene = Gameplay::create();
	return scene;
}

bool Gameplay::init()
{
	if (!Scene::init())
		return false;

	isTransitioning = false;

	srand(time(NULL)); //seed rng
	director = Director::getInstance();
	//Setting the default animation rate for the director
	director->setAnimationInterval(1.0f/60.0f);
	director->setDisplayStats(1); //Remove this after debugging
	
	initGameObjects();
	initSprites();
	initListeners();

	scheduleUpdate();

	return true;
}

//initializes the user interface
void Gameplay::initUI()
{

}

void Gameplay::initGameObjects()
{
	Hero::hero->moveState = Hero::MoveDirection::idle;

	GameObject::MAX_X = 1856.0f;
	GameObject::MAX_Y = 952.0f;

	boss = new Boss(Hero::hero, this);
}

void Gameplay::initSprites()
{
	//add background
	background = Sprite::create("Backgrounds/background.png");
	background->setAnchorPoint(Vec2(0.0f, 0.0f));
	this->addChild(background, 1);

	//get the tilemap in
	cocos2d::TMXTiledMap* testTileMap = TMXTiledMap::create("Tilemaps/bossMap.tmx"); //ayy it works
	addChild(testTileMap, 1);

	cocos2d::TMXLayer* groundLayer = testTileMap->getLayer("tiles");
	cocos2d::TMXLayer* platformLayer = testTileMap->getLayer("platforms");
	//cocos2d::TMXLayer* pillarLayer = testTileMap->getLayer("pillars");

	unsigned int tileMapWidth = testTileMap->getMapSize().width;   //map width
	unsigned int tileMapHeight = testTileMap->getMapSize().height; //map height
	for (unsigned int x = 0; x < tileMapWidth; x++)       //width of map grid
	{
		for (unsigned int y = 0; y < tileMapHeight; y++)  //height of map grid
		{
			cocos2d::Sprite* currentTile = groundLayer->getTileAt(Vec2(x, y));
			if (currentTile != NULL)
			{
				GroundTile* newGroundTile = new GroundTile(currentTile->getPosition(), 64);

				//set collision flags if there are adjacent ground tiles
				//we have to do our own x and y validation because cocos sucks and crashes otherwise
				if (x != 0)
				{
					if (groundLayer->getTileAt(Vec2(x - 1, y)) != NULL)
						newGroundTile->ignoreLeftCollision = true;
				}
				if (x != tileMapWidth - 1)
				{
					if (groundLayer->getTileAt(Vec2(x + 1, y)) != NULL)
						newGroundTile->ignoreRightCollision = true;
				}
				if (y != 0)
				{
					if (groundLayer->getTileAt(Vec2(x, y - 1)) != NULL)
						newGroundTile->ignoreTopCollision = true;
				}
				if (y != tileMapHeight - 1)
				{
					if (groundLayer->getTileAt(Vec2(x, y + 1)) != NULL)
						newGroundTile->ignoreBottomCollision = true;
				}
			}

			currentTile = platformLayer->getTileAt(Vec2(x, y));
			if (currentTile != NULL)
			{
				PlatformTile* newPlatformTile = new PlatformTile(currentTile->getPosition(), 64);
			}
		}
	}

	//add hero (singleton class)
	Hero::hero->sprite = Sprite::create("Sprites/shooting_test.png");
	this->addChild(Hero::hero->sprite, 20);
	Hero::hero->sprite->setPosition(Vec2(700, 200));
	HeroStateManager::idle->onEnter();

	Hero::hero->arm = cocos2d::Sprite::create("Sprites/arm_right.png");
	this->addChild(Hero::hero->arm, 21); //add hero arm
	Hero::hero->arm->setVisible(0); //make arm invisible to begin with

	//add boss
	this->addChild(boss->getSprite(), 17);

	//add hero hurtbox FOR TESTING PURPOSES
	testHurtbox = DrawNode::create();
	this->addChild(testHurtbox, 30);
	//add fire melee attack hixbox FOR TESTING PURPOSES
	testMeleeAttack = DrawNode::create();
	this->addChild(testMeleeAttack, 40);

	//add grapple sprite
	//add repeating pattern to grapple sprite
	Grapple::grapple->sprite = Sprite::create("Sprites/testGrapple.png");
	Texture2D::TexParams params;
	params.minFilter = GL_NEAREST;
	params.magFilter = GL_NEAREST;
	params.wrapS = GL_REPEAT;
	params.wrapT = GL_REPEAT;
	Grapple::grapple->sprite->getTexture()->setTexParameters(params);
	Grapple::grapple->sprite->setVisible(0);
	Grapple::grapple->sprite->setAnchorPoint(Vec2(0.5, 0));
	this->addChild(Grapple::grapple->sprite, 5);

	//grapple tip
	Grapple::grapple->tip = Sprite::create("Sprites/grappleTip.png");
	Grapple::grapple->tip->setAnchorPoint(Vec2(0.5, 0));
	this->addChild(Grapple::grapple->tip, 6);

	//grapple destination indicator
	Grapple::grapple->indicator = Sprite::create("Sprites/grappleIndicator.png");
	Grapple::grapple->indicator->setVisible(0);
	this->addChild(Grapple::grapple->indicator, 7);
}

void Gameplay::initListeners()
{
	mouseAndKeyboardHandler = new MouseAndKeyboardHandler(_eventDispatcher, this);

	//init controller listener
	controllerHandler = new ControllerHandler(_eventDispatcher, this);
}

//UPDATE
void Gameplay::update(float dt)
{
	if (!isTransitioning)
	{
		Grapple::grapple->update(dt, this); //update grapple
		Hero::hero->update(dt); //update our hero

		testHurtbox->clear();
		//DRAW HURTBOX FOR TESTING
		testHurtbox->drawSolidRect(Vec2(Hero::hero->hurtBox.origin),
			Vec2(Hero::hero->hurtBox.origin.x + Hero::hero->hurtBox.size.width,
				Hero::hero->hurtBox.origin.y + Hero::hero->hurtBox.size.height),
			Color4F(1.0f, 0.0f, 0.0f, 0.f));
		//DRAW MOVEBOX FOR TESTING
		testHurtbox->drawSolidRect(Vec2(Hero::hero->moveBox.origin.x, Hero::hero->moveBox.origin.y),
			Vec2(Hero::hero->moveBox.origin.x + Hero::hero->moveBox.size.width,
				Hero::hero->moveBox.origin.y + Hero::hero->moveBox.size.height),
			Color4F(0.0f, 1.0f, 0.0f, .0f));
		//DRAW BOSS HITBOX FOR TESTING


		testMeleeAttack->clear();
		//DRAW MELEE ATTACK HITBOX FOR TESTING
		testMeleeAttack->drawSolidRect(HeroAttackManager::currentAttack->hitbox.origin,
			Vec2(HeroAttackManager::currentAttack->hitbox.getMaxX(), HeroAttackManager::currentAttack->hitbox.getMaxY()),
			Color4F(1.0f, 0.7f, 0.8f, 0.3f));

		spawnEnemies();     //spawn enemies if needed 
		updateObjects(dt);  //update objects
		updateEnemies(dt);  //update enemies

		//FOR TESTING BOSS DEATH
		if (boss->getHealth() == 0) //This can be done through boss instead
		{
			//Hero::hero->reset(); //reset hero
			//TileBase::deleteAllTiles();
			//director->replaceScene(TransitionFade::create(2.0f, VictoryScreen::createScene(), Color3B(0, 0, 0)));
			//isTransitioning = true;
		}
		else if (Hero::hero->health == 0)
		{
			Hero::hero->reset(); //reset hero
			TileBase::deleteAllTiles();
			director->replaceScene(TransitionFade::create(2.0f, DeathScreen::createScene(), Color3B(0, 0, 0)));
			isTransitioning = true;
		}
	}
}

void Gameplay::spawnEnemies()
{
	//spawns all enemies to keep a certain amount of each in the map
	
}

void Gameplay::updateObjects(const float& dt)
{
	//update all platforms
	unsigned int numPlatforms = Platform::platformList.size();
	for (unsigned int i = 0; i < numPlatforms; i++)
		Platform::platformList[i]->update();

	//update all ice projectiles
	for (unsigned int i = 0; i < IceProjectile::iceProjectileList.size(); i++)
		IceProjectile::iceProjectileList[i]->update(dt);
}

void Gameplay::updateEnemies(const float& dt)
{
	//update boss
	boss->update(dt);

	//check for an attack hitting the boss
	HeroAttackBase* currentAttack = HeroAttackManager::currentAttack;
	if (currentAttack == HeroAttackManager::meleeFire && myHelper::isCollision(currentAttack->hitbox, boss->getHitBox()))
	{
		currentAttack->disabled = true;
		boss->takeDamage();
	}

	//check for collision on boss
	if (Hero::hero->isHitboxCollision(boss->getHitBox()))
	{
		Hero::hero->takeDamage();
	}

	//loop through each attack checking for collisions
	unsigned int attackListSize = boss->getLavaList().size();

	/*for (unsigned int i = 0; i < attackListSize; i++)
	{
		if (Hero::hero->isHitboxCollision(boss->getLavaList()[i]->getHitBox())) 
		{
			Hero::hero->takeDamage();

		}
	}*/

	for (auto i : boss->getLavaList())
	{
		if (Hero::hero->isHitboxCollision(i->getHitBox()))
		{
			Hero::hero->takeDamage();
			i->hitByHero();
		}
	}
}

//removes all game objects from the world
void Gameplay::removeAllObjects()
{
	
}

