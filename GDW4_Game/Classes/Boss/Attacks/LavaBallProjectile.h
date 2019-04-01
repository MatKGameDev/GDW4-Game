#pragma once
#include "Boss/Attacks/Boss1Attack.h"

class LavaBall : public Boss1LavaAttack
{
public:
	LavaBall(int order, Boss *bossInstance);
	~LavaBall();

	//Functions
	void update(const float &deltaT) override;
	void hitByEnvironment() override;
private:
	float waitingTime;
	bool isWaiting{ true };
};
