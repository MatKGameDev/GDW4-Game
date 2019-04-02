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
	void changeToIdleState() const; //Idle state is allowed to change publicly
	void changeToDeathState() const; //Dealth state is allowed to change publicly

protected:
	Boss *bossPointer;

	/*
	 * State changes functions. These can only
	 * be changes through inheritance
	 */
	void changeToFlameSplit() const;
	void changeToFlameThrower() const;
	void changeToExplosiveBullet() const;
	void changeToRestingState() const;
};