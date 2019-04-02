#pragma once
#ifndef ICEPROJECTILE_H
#define ICEPROJECTILE_H

#include "GameObject.h"

class IceProjectile : public GameObject
{
public:
	IceProjectile();
	IceProjectile(Vect2 startVelocity);

	static const float SPEED;
	static std::vector<IceProjectile*> iceProjectileList;

	void removeAndDelete();
	void checkAndResolveOutOfBounds();
	void updateHitboxes() override;
	void update(float dt);
};
#endif