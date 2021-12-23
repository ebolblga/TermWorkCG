#include "Point.h"
#include <math.h>
const double pi = 3.141592653589793238463;
Point* Point::rotate(double angle, Point* p)
{
	double w = this->x - p->x;
	double h = this->y - p->y;
	double r = sqrt(w * w + h * h);
	double a = atan(h / w);
	if (w < 0) a += pi;
	this->x = p->x + r * cos(a + angle);
	this->y = p->y + r * sin(a + angle);
	return this;
}
void Point::reverse() {
	x = -x;
	y = -y;
	z = -z;
}