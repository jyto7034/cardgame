#pragma once
#include "Vector.h"
#include "Enum.h"

class AbstractObject {
public:
	RENDER_PRIORITY priority;
	Vector position;
	int ObjectID;
	AbstractObject() : position(Vector(0, 0)), ObjectID(-1), priority(RENDER_PRIORITY::PRIORITY_NULL){}
	virtual ~AbstractObject() {}
};