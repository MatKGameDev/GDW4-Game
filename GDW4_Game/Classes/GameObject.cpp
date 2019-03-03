#include "GameObject.h"

//set static const/variables
const float GameObject::MAX_X = 1477;
const float GameObject::MAX_Y = 985;
const Vect2 GameObject::GRAVITY = Vect2(0, -250); //set gravity

GameObject::GameObject(Vect2 position, std::string spriteFilePath) :
	theta(0.0f),
	mass(1.0f),
	gravityMultiplier(1.0f)
{
	//create sprite and set initial values
	sprite = Sprite::create(spriteFilePath);
	sprite->setPosition(Vec2(position.x, position.y));
	width = sprite->getBoundingBox().size.width;
	height = sprite->getBoundingBox().size.height;
	
	//initially set hitboxes to the sprite's size, each game object can modify these in their own classes as necessary
	moveBox.setRect(getLeftSidePos(), getBottomPos(), width, height);
	hurtBox.setRect(getLeftSidePos(), getBottomPos(), width, height);

	velocity.set(0.f, 0.f);
	acceleration.set(0.f, 0.f);
	force.set(0.f, 0.f);
}

GameObject::~GameObject()
{
	sprite = NULL; //delete sprite
}

//gets poition of the sprite (middle)
Vect2 GameObject::getPosition()
{
	return Vect2(sprite->getPosition());
}

//get the position (x or y) for the left, right, bottom and top edges of the sprite
float GameObject::getLeftSidePos()
{
	return getPosition().x - width / 2;
}
float GameObject::getRightSidePos()
{
	return getPosition().x + width / 2;
}
float GameObject::getBottomPos()
{
	return getPosition().y - height / 2;
}
float GameObject::getTopPos()
{
	return getPosition().y + height / 2;
}

//removes the sprite from the screen and deletes it
void GameObject::destroySprite()
{
	sprite->runAction(RemoveSelf::create());
	delete this;
}

//checks for collision on two AABB objects movement hitboxes
bool GameObject::isMovementCollision(GameObject* otherObject)
{
	//check x values to see if they arent touching
	//assuming sprites are named A and B:
	//A_begin.x > B_end.x OR B_begin.x > A_end.x means there IS a gap on x
	if (this->moveBox.getMinX() >= otherObject->moveBox.getMaxX() || otherObject->moveBox.getMinX() >= this->moveBox.getMaxX())
		return false;
	//check y values to see if they arent touching
	//A_begin.y > B_end.y OR B_begin.y > A_end.y means there IS a gap on y
	else if (this->moveBox.getMinY() >= otherObject->moveBox.getMaxY() || otherObject->moveBox.getMinY() >= this->moveBox.getMaxY())
		return false;
	//if neither, there's a collision
	else
		return true;
}

//updates the object's physics properties
void GameObject::updatePhysics(float dt)
{
	acceleration = force + (GRAVITY * gravityMultiplier * mass);
	velocity += acceleration * dt; //update velocity
	sprite->setPosition(sprite->getPosition() + Vec2(velocity.x, velocity.y) * dt); //update position
}