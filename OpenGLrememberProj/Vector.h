#pragma once
class Vector
{
private:
public:
	double x = 0;
	double y = 0;
	double z = 0;
	double w = 0;
	Vector(double x, double y, double z, double w);
	Vector operator +(Vector v);
	Vector operator -(Vector v);
	Vector operator +=(Vector v);
	Vector operator -=(Vector v);
	Vector operator *(Vector v);
	Vector operator*(double s);
	Vector operator *=(Vector v);
	double size();
	Vector normolize();
};

