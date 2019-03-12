#pragma once

//Foward declare
class Boss;


/*
 *
 */
class FirstBossState
{
public:
	FirstBossState();
	virtual ~FirstBossState();
	virtual void update(const float &deltaT, Boss *bossInstance) = 0;

	//Only Idle state is allow to change publicly
	virtual void changeToIdleState(Boss *boss);
protected:
	enum State
	{
		charging, performingAbility
	};

	State *currentState{nullptr};

	//Utility Functions
	virtual void changeToFlameSplit(Boss *boss);
	virtual void changeToFlameThrower(Boss *boss);
	virtual void changeToSuckingBullet(Boss *boss);
};

/*
 *
 */
class Idling4FirstBoss: public FirstBossState
{
public:
	Idling4FirstBoss();
	void update(const float &deltaT, Boss *bossInstance) override;

private:
	float cooldownBeforeNextAbility;

	//Utility functions
	/*
	 * List	of utility functions
	 * 1. Choose a random ability
	 */
	void chooseRandomAbility(Boss *bossInstance);
};

/*
 *This class  
 */
class FlameSplit4FirstBoss: public FirstBossState
{
public:
	FlameSplit4FirstBoss();
	void update(const float &deltaT, Boss *bossInstance) override;
private:
};

class FlameThrower4FirstBoss : public FirstBossState
{
public:
	FlameThrower4FirstBoss();

	void update(const float& deltaT, Boss* bossInstance) override;
private:
};

class SuckingAbility4FirstBoss: public FirstBossState
{
public:
	SuckingAbility4FirstBoss();

	void update(const float& deltaT, Boss* bossInstance) override;
};