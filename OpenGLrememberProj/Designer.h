#pragma once
#include <Windows.h>
#include <GL\GL.h>
#include <GL\GLU.h>
#include "Point.h";
#include "Vector.h"
#include <vector>
using namespace std;	
class Designer
{
public:
	double height = 20;
	Point MainPoint;
	Point center;
	int curvePointCount = 30;
	double angle = 0;
	int twists = 0;
	int textureId = 0;
	double size[2] = { 0, 0};
	double cover[4] = { 0 ,0, 0, 0 };
	double cover1[4] = { 0 ,0, 0, 0 };
	double wall[4] = { 0 ,0, 0, 0 };
	double corners[4] = { -999, -999, -999,  };
	double countour = 0;
	double xcountour = 0;
	Point* lastPoint = NULL;
	vector<Point*> points;

	Designer(double height);
	void addPoint(double x = 0, double y = 0, double z = 0, Type t = Line);
	void Draw();
	void SetTexture(int textureId, double width, double height);
	void CoverTexture(double x1, double y1, double x2, double y2);
	void Cover1Texture(double x1, double y1, double x2, double y2);
	void WallTexture(double x1, double y1, double x2, double y2);
	double changeCounter(Point* p);
	//void DrawWalls();
	void preInit();
	Point* getCoverCoord(double x, double y);
	Point* getCoverCoord1(double x, double y);
	double getWallCoord(Point* p);
	Point* getWallCoords(Point* p);
	void DrawWalls(vector<Point*> ps1, vector<Point*> ps2);
	void DrawCover(vector<Point*> ps);
	void DrawCover1(vector<Point*> ps);
	void changeCorners(double x, double y);
	//void DrawCover(double z=0);
	void addCircle(double x, double y, double z);
};

