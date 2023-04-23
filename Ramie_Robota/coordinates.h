#pragma once
struct Coordinates
{
	float x;
	float y;
	float z;
	Coordinates(float x = 0.0f, float y = 0.0f, float z = 0.0f) {
		this->x = x;
		this->y = y;
		this->z = z;
	}
};