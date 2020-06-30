#pragma once
#include <iostream>

class Vector {
private:
	void _Forward();
	float dx, dy;
public:
	float x, y, speed;
	Vector(int _x, int _y) : x(_x), y(_y), dx(-1), dy(-1), speed(-1) {}
	Vector() : x(-1), y(-1), dx(-1), dy(-1), speed(-1) {}

	static void Forward(Vector*, Vector, int);

	Vector operator-(const Vector& rv) { return Vector((this->x - rv.x) * 10, (this->y - rv.y) * 14);   }
	Vector operator+(const Vector& rv) { return Vector((this->x + rv.x) * 10, (this->y + rv.y) * 14); }

	void showData() { std::cout << "x :" << x << ", y :" << y << std::endl; }
};