#pragma once
#ifndef VECT2_H
#define VECT2_H

#include "cocos2d.h"

class Vect2
{
public:
	float x;
	float y;

	Vect2();
	Vect2(const float x, const float y);
	Vect2(cocos2d::Vec2 vector);

	Vect2 operator+(const Vect2 a) const;
	Vect2 operator-(const Vect2 a) const;
	Vect2 operator*(const Vect2 a) const;
	Vect2 operator/(const Vect2 a) const;

	Vect2 operator+=(const Vect2 a);
	Vect2 operator-=(const Vect2 a);
	Vect2 operator*=(const Vect2 a);
	Vect2 operator/=(const Vect2 a);

	Vect2 operator*(const float scalar) const;
	Vect2 operator/(const float scalar) const;
	Vect2 operator+(const float scalar) const;
	Vect2 operator-(const float scalar) const;

	Vect2 operator+=(const float scalar);
	Vect2 operator-=(const float scalar);
	Vect2 operator*=(const float scalar);
	Vect2 operator/=(const float scalar);

	friend bool operator> (const Vect2 vector, const float scalar);
	friend bool operator< (const Vect2 vector, const float scalar);

	friend bool operator> (const Vect2 lhs, const Vect2 rhs);
	friend bool operator< (const Vect2 lhs, const Vect2 rhs);

	friend Vect2 operator+(const float a, const Vect2 b);
	friend Vect2 operator-(const float a, const Vect2 b);

	Vect2 operator-() const;

	const float & Vect2::operator[](int index) const;
	float & Vect2::operator[](int index);

	void set(float newX, float newY);
	float getMagnitude();
	float getMagnitudeSquared();
	float getNormalized();
	float dotProduct(const Vect2 rhs);
	float crossProduct(const Vect2 rhs);
	
	static float calculateDistance(const Vect2 vectA, const Vect2 vectB);
	static float calculateDistanceSquared(const Vect2 vectA, const Vect2 vectB);
	static Vect2 lerp(Vect2 vectA, Vect2 vectB, float scaleFactor);
};
#endif