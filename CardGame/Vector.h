#pragma once
#include <iostream>
#include "Enum.h"

class CVector {
private:
	int count;
public:
	int prevObject;
	std::vector<float> objList;
	CVector() : count(0), prevObject(0){}
	CVector(std::vector<float> v_obj) : objList(v_obj), count(0), prevObject(0){}

	int PeekObject() {
		if (count < objList.size())
		{
			prevObject = count < objList.size() ? objList[count] : -1;
			return count < objList.size() ? objList[count++] : -1;
		}
		return -1;
	}
};

class Vector {
private:
	void _Forward();
	void _Lerp();
public:
	int speed;
	int dx, dy;
	int x, y;
	float t;
	std::map<const char*, CVector>* calculated_vector;
	Vector(int _x, int _y) : x(_x), y(_y), dx(-1), dy(-1), speed(-1), t(-1), calculated_vector() {}
	Vector(int _x, int _y, int _dx, int _dy) : x(_x), y(_y), dx(_dx), dy(_dy), speed(-1), t(-1), calculated_vector() {}
	Vector() : x(-1), y(-1), dx(-1), dy(-1), speed(-1), t(-1), calculated_vector() {}
	~Vector() {};

	static void Forward(Vector*, Vector, int);
	static void Lerp(Vector*, Vector, float);

	Vector operator-(const Vector& rv) { return Vector((this->x - rv.x) * 10, (this->y - rv.y) * 14);   }
	Vector operator+(const Vector& rv) { return Vector((this->x + rv.x) * 10, (this->y + rv.y) * 14); }

	void showData() { std::cout << "x :" << x << ", y :" << y << std::endl; }
};