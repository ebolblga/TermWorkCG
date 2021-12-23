#include "Vector.h"
#include "math.h"
double sqr(double x) {
	return x * x;
}
Vector::Vector(double x = 0, double y = 0, double z = 0, double w = 1) {
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}
Vector Vector::operator+ (Vector v) {
	return Vector(v.x + this->x, v.y + this->y, v.z + this->z);
}
Vector Vector::operator -(Vector v) {
	return Vector(this->x - v.x, this->y - v.y, this->z - v.z);
}
Vector Vector::operator+= (Vector v) {
	this->x += v.x;
	this->y += v.y;
	this->z += v.z;
	return *this;
}
Vector Vector::operator -=(Vector v) {
	this->x -= v.x;
	this->y -= v.y;
	this->z -= v.z;
	return *this;
}
Vector Vector::operator* (Vector v) {
	Vector res;
	res.w = this->w * v.w - this->x * v.x - this->y * v.y - this->z * v.z;
	res.x = this->w * v.x + this->x * v.w + this->y * v.z - this->z * v.y;
	res.y = this->w * v.y - this->x * v.z + this->y * v.w + this->z * v.x;
	res.z = this->w * v.z + this->x * v.y - this->y * v.x + this->z * v.w;
	return res;
}
Vector Vector::operator* (double s) {
	Vector res;
	res.w = this->w * s;
	res.x = this->w * s;
	res.y = this->w * s;
	res.z = this->w * s;
	return res;
}
Vector Vector::operator*= (Vector v) {
	this->w = this->w * v.w - this->x * v.x - this->y * v.y - this->z * v.z;
	this->x = this->w * v.x + this->x * v.w + this->y * v.z - this->z * v.y;
	this->y = this->w * v.y - this->x * v.z + this->y * v.w + this->z * v.x;
	this->z = this->w * v.z + this->x * v.y - this->y * v.x + this->z * v.w;
	return *this;
}
double Vector::size() {
	return sqrt(sqr(this->x) + sqr(this->y) + sqr(this->z));
}
Vector Vector::normolize() {
	double size = this->size();
	return Vector(this->x / size,this->y / size,this->z / size);
}
