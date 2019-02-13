#pragma once
#include "GameObject.h"

class IceProjectile : public GameObject
{
public:
	IceProjectile(Vect2 startVelocity);

	static const float SPEED;
	static std::vector<IceProjectile*> iceProjectileList;

	void removeAndDelete();
	void checkAndResolveOutOfBounds();
	void update(float dt);
};