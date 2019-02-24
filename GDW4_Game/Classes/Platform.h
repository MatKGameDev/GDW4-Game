#pragma once
#include "Hero.h"

class Platform : public GameObject
{
public:
	Platform(Vect2 position);

	static std::vector<Platform*> platformList;

	bool checkOneWayCollision(GameObject* otherObject);
	void updateHitboxes() override;
	void update();
};

