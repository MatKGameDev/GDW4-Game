#pragma once

//Foward declare
class Boss;

class FirstBossState
{
public:
	//Constructors and Destructor
	FirstBossState(Boss *bossInstance);
	virtual ~FirstBossState() = default;

	//Member functions
	virtual void update(const float& deltaTime);
	virtual void changeToIdleState(); //Only Idle state is allow to change publicly

protected:
	Boss *bossPointer;

	//Utility Functions
	virtual void changeToFlameSplit();
	virtual void changeToFlameThrower();
	virtual void changeToExplosiveBullet();
};