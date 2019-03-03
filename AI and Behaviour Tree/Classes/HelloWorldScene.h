#pragma once

#include "cocos2d.h"
#include "Boss.h"
#include "Boss1Attack.h"

class HelloWorld : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    bool init() override;
    
    // a selector callback

	void update(float delta) override;

    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
private:
	Boss *firstBoss{nullptr};
	Boss1LavaAttack *attack{ nullptr };
};
