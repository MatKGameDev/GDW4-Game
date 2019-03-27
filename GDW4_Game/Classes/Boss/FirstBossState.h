#pragma once

//Foward declare
class Boss;

/*
 *
 */
class FirstBossSmallerState
{
protected:
	Boss* bossPointer;

	FirstBossSmallerState(Boss *aBossInstance);
public:
	virtual ~FirstBossSmallerState();

	virtual void update(float deltaT);
	
};

class FirstBossState
{
public:
	//Destructor
	virtual ~FirstBossState();

	//Setter
	void setSmallerState(FirstBossSmallerState *newState);

	//Functions
	virtual void update(const float &deltaT, Boss *bossInstance) = 0;
	virtual void changeToIdleState(Boss *boss); //Only Idle state is allow to change publicly
protected:
	FirstBossSmallerState *currentState{ nullptr };

	//Utility Functions
	virtual void changeToFlameSplit(Boss *boss);
	virtual void changeToFlameThrower(Boss *boss);
	//virtual void changeToSuckingBullet(Boss *boss);
};
