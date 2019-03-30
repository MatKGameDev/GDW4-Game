#include "Tutorial.h"
#include "Gameplay.h"
#include "PrettyPictureScene.h"
#include <iostream>
#include "HeroStateManager.h"
#include "PauseMenu.h"
#include "HelpBubble.h"
#include "ControllerInput.h"
#include "Input Handler/InputHandler.h"

cocos2d::Scene* Tutorial::createScene()
{
	Scene* scene = Tutorial::create();
	return scene;
}

bool Tutorial::init()
{
	if (!Scene::init())
		return false;

	isTransitioning = false;
	srand(time(NULL)); //seed rng
	director = Director::getInstance();
	//Setting the default animation rate for the director
	director->setAnimationInterval(1.0f / 60.0f);
	director->setDisplayStats(1); //Remove this after debugging

	initUI();
	initGameObjects();
	initSprites();
	initListeners();

	scheduleUpdate();

	return true;
}

//initializes the user interface
void Tutorial::initUI()
{
	//initialize help bubbles
	HelpBubble* jumpHint = new HelpBubble("Sprites/jumpHintTest.png", cocos2d::Vec2(190, 400), 200, 500);
	this->addChild(jumpHint->sprite, 18);

	HelpBubble* holdJumpHint = new HelpBubble("Sprites/holdJumpHint.png", cocos2d::Vec2(1150, 300), 800, 1200);
	holdJumpHint->sprite->setScale(3.0);
	this->addChild(holdJumpHint->sprite, 18);
}

void Tutorial::initGameObjects()
{
	//set bounds for the scene
	GameObject::MAX_X = 15000.0f;
	GameObject::MAX_Y = 1080.0f;
}

void Tutorial::initSprites()
{
	Vec2 origin = Director::sharedDirector()->getVisibleOrigin(); //origin point
	Size size = Director::sharedDirector()->getVisibleSize();  //screen size
	Vec2 center = Vec2(size.width / 2 + origin.x, size.height / 2 + origin.y); //center point

	fieldWidth = size.width * 4;  //x boundary for camera
	fieldHeight = size.height - 40; //y boundary for camera

	Texture2D::TexParams params;
	params.minFilter = GL_NEAREST;
	params.magFilter = GL_NEAREST;
	params.wrapS = GL_REPEAT;
	params.wrapT = GL_REPEAT;

	//add background layers
	backgroundL1 = Sprite::create("Backgrounds/tutBackground_L1.png");
	backgroundL1->setAnchorPoint(Vec2(0.0f, 0.0f));
	backgroundL1->getTexture()->setTexParameters(params);
	backgroundL1->setTextureRect(cocos2d::Rect(0, 0, fieldWidth, fieldHeight));

	backgroundL2 = Sprite::create("Backgrounds/tutBackground_L2.png");
	backgroundL2->setAnchorPoint(Vec2(0.0f, 0.0f));
	backgroundL2->getTexture()->setTexParameters(params);
	backgroundL2->setTextureRect(cocos2d::Rect(0, 0, fieldWidth, fieldHeight));

	backgroundL3 = Sprite::create("Backgrounds/tutBackground_L3.png");
	backgroundL3->setAnchorPoint(Vec2(0.0f, 0.0f));
	backgroundL3->getTexture()->setTexParameters(params);
	backgroundL3->setTextureRect(cocos2d::Rect(0, 0, fieldWidth, fieldHeight));

	backgroundL4 = Sprite::create("Backgrounds/tutBackground_L4.png");
	backgroundL4->setAnchorPoint(Vec2(0.0f, 0.0f));
	backgroundL4->getTexture()->setTexParameters(params);
	backgroundL4->setTextureRect(cocos2d::Rect(0, 0, fieldWidth, fieldHeight));

	backgroundL5 = Sprite::create("Backgrounds/tutBackground_L5.png");
	backgroundL5->setAnchorPoint(Vec2(0.0f, 0.0f));
	backgroundL5->getTexture()->setTexParameters(params);
	backgroundL5->setTextureRect(cocos2d::Rect(0, 0, fieldWidth, fieldHeight));

	backgroundL6 = Sprite::create("Backgrounds/tutBackground_L6.png");
	backgroundL6->setAnchorPoint(Vec2(0.0f, 0.0f));
	backgroundL6->getTexture()->setTexParameters(params);
	backgroundL6->setTextureRect(cocos2d::Rect(0, 0, fieldWidth, fieldHeight));

	backgroundL7 = Sprite::create("Backgrounds/tutBackground_L7.png");
	backgroundL7->setAnchorPoint(Vec2(0.0f, 0.0f));
	backgroundL7->getTexture()->setTexParameters(params);
	backgroundL7->setTextureRect(cocos2d::Rect(0, 0, fieldWidth, fieldHeight));

	backgroundL8 = Sprite::create("Backgrounds/tutBackground_L8.png");
	backgroundL8->setAnchorPoint(Vec2(0.0f, 0.0f));
	backgroundL8->getTexture()->setTexParameters(params);
	backgroundL8->setTextureRect(cocos2d::Rect(0, 0, fieldWidth, fieldHeight));

	backgroundL9 = Sprite::create("Backgrounds/tutBackground_L9.png");
	backgroundL9->setAnchorPoint(Vec2(0.0f, 0.0f));
	backgroundL9->getTexture()->setTexParameters(params);
	backgroundL9->setTextureRect(cocos2d::Rect(0, 0, fieldWidth, fieldHeight));

	backgroundL10 = Sprite::create("Backgrounds/tutBackground_L10.png");
	backgroundL10->setAnchorPoint(Vec2(0.0f, 0.0f));
	backgroundL10->getTexture()->setTexParameters(params);
	backgroundL10->setTextureRect(cocos2d::Rect(0, 0, fieldWidth, fieldHeight));

	
	
	foregroundL1 = Sprite::create("Backgrounds/foreground1.png");
	foregroundL1->setAnchorPoint(Vec2(0.0f, 0.0f));
	foregroundL1->getTexture()->setTexParameters(params);
	foregroundL1->setTextureRect(cocos2d::Rect(0, -464, fieldWidth, 2048));

	foregroundL2 = Sprite::create("Backgrounds/foreground2.png");
	foregroundL2->setAnchorPoint(Vec2(0.0f, 0.0f));
	foregroundL2->getTexture()->setTexParameters(params);
	foregroundL2->setTextureRect(cocos2d::Rect(0, -464, fieldWidth, 2048));

	//create parallax node for background layers
	ParallaxNode* backGroundParallax = ParallaxNode::create();
	ParallaxNode* foregroundParallax = ParallaxNode::create();

	//add background layers to the parallax node with various scrolling speeds, push them all up a bit by using the offset
	backGroundParallax->addChild(backgroundL1, -20, Vec2(0.05, 0.05), Vec2(0, 100));
	backGroundParallax->addChild(backgroundL2, -19, Vec2(0.1, 0.1), Vec2(0, 100));
	backGroundParallax->addChild(backgroundL3, -18, Vec2(0.14, 0.14), Vec2(0, 100));
	backGroundParallax->addChild(backgroundL4, -17, Vec2(0.32, 0.32), Vec2(0, 100));
	backGroundParallax->addChild(backgroundL5, -16, Vec2(0.41, 0.41), Vec2(0, 100));
	backGroundParallax->addChild(backgroundL6, -15, Vec2(0.54, 0.54), Vec2(0, 100));
	backGroundParallax->addChild(backgroundL7, -14, Vec2(0.71, 0.71), Vec2(0, 100));
	backGroundParallax->addChild(backgroundL8, -13, Vec2(0.85, 0.85), Vec2(0, 100));
	backGroundParallax->addChild(backgroundL9, -12, Vec2(0.91, 0.91), Vec2(0, 100));
	backGroundParallax->addChild(backgroundL10, -12, Vec2(0.91, 0.91), Vec2(0, 100));
	
	
	foregroundParallax->addChild(foregroundL1, 91, Vec2(1.3, 1.3), Vec2(0, 00)); //foreground 1
	foregroundParallax->addChild(foregroundL2, 90, Vec2(1.1, 1.1), Vec2(0, 00)); //foreground 2



	this->addChild(backGroundParallax, -5);

	this->addChild(foregroundParallax, 90);

	//get the tilemap in
	cocos2d::TMXTiledMap* testTileMap = TMXTiledMap::create("Tilemaps/tutTest3.tmx"); //ayy it works
	addChild(testTileMap, 1);

	cocos2d::TMXLayer* groundLayer = testTileMap->getLayer("Ground");
	cocos2d::TMXLayer* platformLayer = testTileMap->getLayer("platforms");

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
	Hero::hero->sprite->setPosition(Vec2(20, 200));
	Hero::hero->lookState = Hero::LookDirection::lookingRight;
	HeroStateManager::idle->onEnter();

	//use a follow camera with strict dimensions for horizontal scrolling
	this->runAction(Follow::create(Hero::hero->sprite, Rect(0, 50, fieldWidth, fieldHeight)));

	Hero::hero->arm = cocos2d::Sprite::create("Sprites/arm_right.png");
	this->addChild(Hero::hero->arm, 21); //add hero arm
	Hero::hero->arm->setVisible(0); //make arm invisible to begin with

	//add hero hurtbox FOR TESTING PURPOSES
	testHurtbox = DrawNode::create();
	this->addChild(testHurtbox, 30);
	//add fire melee attack hixbox FOR TESTING PURPOSES
	testMeleeAttack = DrawNode::create();
	this->addChild(testMeleeAttack, 40);

	//add grapple sprite
	//add repeating pattern to grapple sprite
	Grapple::grapple->sprite = Sprite::create("Sprites/testGrapple.png");
	Grapple::grapple->sprite->getTexture()->setTexParameters(params);
	Grapple::grapple->sprite->setVisible(0);
	Grapple::grapple->sprite->setAnchorPoint(Vec2(0.5, 0));
	this->addChild(Grapple::grapple->sprite, 5);

	//grapple tip sprite
	Grapple::grapple->tip = Sprite::create("Sprites/grappleTip.png");
	Grapple::grapple->tip->setAnchorPoint(Vec2(0.5, 0));
	this->addChild(Grapple::grapple->tip, 6);

	//grapple destination indicator
	Grapple::grapple->indicator = Sprite::create("Sprites/grappleIndicator.png");
	Grapple::grapple->indicator->setVisible(0);
	this->addChild(Grapple::grapple->indicator, 7);
}

/**
 * This function initialize the mouse, keyboard, and controller handlers. 
 * Any input with those three will be process by the Handler instead
 */
void Tutorial::initListeners()
{
	mouseAndKeyboardHandler = new MouseAndKeyboardHandler(_eventDispatcher,this);
	controllerHandler = new ControllerHandler(_eventDispatcher, this);
}

//UPDATE
void Tutorial::update(float dt)
{
	if (!isTransitioning)
	{
		Grapple::grapple->update(dt, this); //update grapple
		Hero::hero->update(dt); //update our hero

		testHurtbox->clear();
		//DRAW HURTBOX FOR TESTING
		testHurtbox->drawSolidRect(Vec2(Hero::hero->hurtBox.origin.x, Hero::hero->hurtBox.origin.y),
			Vec2(Hero::hero->hurtBox.origin.x + Hero::hero->hurtBox.size.width,
				Hero::hero->hurtBox.origin.y + Hero::hero->hurtBox.size.height),
			Color4F(1.0f, 0.0f, 0.0f, 0.f));
		//DRAW MOVEBOX FOR TESTING
		testHurtbox->drawSolidRect(Vec2(Hero::hero->moveBox.origin.x, Hero::hero->moveBox.origin.y),
			Vec2(Hero::hero->moveBox.origin.x + Hero::hero->moveBox.size.width,
				Hero::hero->moveBox.origin.y + Hero::hero->moveBox.size.height),
			Color4F(0.0f, 1.0f, 0.0f, .0f));

		testMeleeAttack->clear();
		//DRAW MELEE ATTACK HITBOX FOR TESTING
		testMeleeAttack->drawSolidRect(HeroAttackManager::currentAttack->hitbox.origin,
			Vec2(HeroAttackManager::currentAttack->hitbox.getMaxX(), HeroAttackManager::currentAttack->hitbox.getMaxY()),
			Color4F(1.0f, 0.7f, 0.8f, 0.2f));

		spawnEnemies();     //spawn enemies if needed 
		updateObjects(dt);  //update objects
		updateEnemies(dt);  //update enemies

		//check if we should move to the next scene
		if (Hero::hero->moveBox.getMaxX() >= 6000)
		{
			Hero::hero->reset();
			HelpBubble::deleteAllInstances();
			director->replaceScene(TransitionFade::create(1.5f, PrettyPictureScene::createScene(), Color3B(0, 0, 0)));
			isTransitioning = true;
		}
	}
	else //we are transitioning
	{
		//move hero down to the nearest block so they arent floating
		Hero::hero->velocity.y = -400;
		Hero::hero->updatePhysics(dt);

		unsigned int tileListSize = TileBase::tileList.size();
		for (unsigned int i = 0; i < tileListSize; i++)
		{
			if (TileBase::tileList[i]->checkAndResolveCollision(Hero::hero))
				HeroStateManager::idle->onEnter();
		}
	}
}

void Tutorial::spawnEnemies()
{
	//spawns all enemies to keep a certain amount of each in the map

}

void Tutorial::updateObjects(const float& dt)
{
	//update all platforms
	for (auto i : Platform::platformList)
		i->update();

	//update all ice projectiles
	for (auto i : IceProjectile::iceProjectileList)
		i->update(dt);

	//update all help bubbles
	for (auto i : HelpBubble::helpBubbleList)
		i->update(dt);
}

void Tutorial::updateEnemies(const float& dt)
{

}

//removes all game objects from the world
void Tutorial::removeAllObjects()
{

}