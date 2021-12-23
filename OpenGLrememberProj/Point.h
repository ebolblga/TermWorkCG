#pragma once
#include "Vector.h"

enum Type {
	Line = 0,
	Circle1,
	CircleRev
};
class Point:public Vector
{
public:
	Type t=Line;
	Point(double x=0, double y=0, double z=0,Type t=Line) :Vector(x, y, z, 1) {
		this->t = t;
	};
	Point* rotate(double angle, Point* p);
	void reverse();
	Point copy() {
		return Point(x, y, z,t);
	}
};

