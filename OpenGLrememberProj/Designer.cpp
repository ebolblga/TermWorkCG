#include "Designer.h"
#include <math.h>
Designer::Designer(double height=3) {
	this->height = height;
}


void Designer::addPoint(double x, double y, double z,Type t) {
	points.push_back(new Point(x,y,z,t));
};
void Designer::changeCorners(double x, double y) {
	if (corners[0] == -999 || x < corners[0]) corners[0] = x;
	if (corners[1] == -999 || y < corners[1]) corners[1] = y;
	if (corners[2] == -999 || x > corners[2]) corners[2] = x;
	if (corners[3] == -999 || y > corners[3]) corners[3] = y;
}
double Designer::changeCounter(Point* p) {
	if (!lastPoint) {
		lastPoint = p;
		return 0;
	}
	countour += sqrt(pow(p->x - lastPoint->x, 2) + pow(p->y - lastPoint->y, 2));
	lastPoint = p;
	return countour;
}
void Designer::preInit() {
	vector<Point*> newPoints;
	lastPoint = NULL;
	countour = 0;
	for (int i = 0; i < points.size(); i++) {
		Point* p = points[i];
		const double pi = 3.141592653589793238463;
		double w1, h1, w2, h2, angle1, angle2, R, a;
		bool rev = false;
		Point* p1;
		Point* p2;
		switch (p->t)
		{
		case Line:
			newPoints.push_back(p);
			changeCorners(p->x, p->y);
			changeCounter(p);
			break;
		case CircleRev:
			rev = true;
		case Circle1:
			p1 = points[i - 1];
			p2 = points[i + 1];
			w1 = p1->x - p->x;
			h1 = p1->y - p->y;
			w2 = p2->x - p->x;
			h2 = p2->y - p->y;
			angle1 = atan(h1 / w1);
			angle2 = atan(h2 / w2);
			if (w1 < 0) angle1 +=pi;
			if (w2 < 0) angle2 +=pi;
			if(!rev) if (angle2 < angle1) angle2 += 2 * pi;
			R = sqrt(w1 * w1 + h1 * h1);
			for (int i = 1; i < curvePointCount-1; i++) {
				a = angle1 + (angle2 - angle1) * i / curvePointCount;
				w1 = p->x + R * cos(a);
				w2 = p->y + R * sin(a);
				Point* pn = new Point(p->x + R * cos(a), p->y + R * sin(a));
				newPoints.push_back(pn);
				changeCorners(p->x + R * cos(a), p->y + R * sin(a));
				changeCounter(pn);
			}
			break;
		default:
			break;
		}
	}
	points = newPoints;
}
Point* Designer::getCoverCoord(double x, double y) {
	double x1 = (x - corners[0]) / (corners[2] - corners[0]);
	double y1 = (y - corners[1]) / (corners[3] - corners[1]);
	double x2 = cover[0] + x1 * (cover[2] - cover[0]);
	double y2 = cover[1] + y1 * (cover[3] - cover[1]);
	return new Point(x2, y2);
}
Point* Designer::getCoverCoord1(double x, double y) {
	double x1 = (x - corners[0]) / (corners[2] - corners[0]);
	double y1 = (y - corners[1]) / (corners[3] - corners[1]);
	double x2 = cover1[0] + x1 * (cover1[2] - cover1[0]);
	double y2 = cover1[1] + y1 * (cover1[3] - cover1[1]);
	return new Point(x2, y2);
}
double Designer::getWallCoord(Point* p) {
	if (!lastPoint) {
		lastPoint = p;
		return 0;
	}
	xcountour += sqrt(pow(p->x - lastPoint->x, 2) + pow(p->y - lastPoint->y, 2));
	lastPoint = p;
	return wall[0] + (wall[2] - wall[0]) * xcountour / countour;
}
Point* Designer::getWallCoords(Point* p) {
	if (!lastPoint) {
		lastPoint = p;
		return new Point(0,wall[1]+(wall[3]-wall[1])*((p->z-center.z)/height));
	}
	xcountour += sqrt(pow(p->x - lastPoint->x, 2) + pow(p->y - lastPoint->y, 2));
	lastPoint = p;
	return new Point(wall[0] + (wall[2] - wall[0]) * xcountour / countour, wall[1] + (wall[3] - wall[1]) * ((p->z - center.z) / height));
}
void Designer::DrawWalls(vector<Point*> ps1, vector<Point*> ps2)
{
	glBindTexture(GL_TEXTURE_2D, textureId);
	glBegin(GL_QUADS);
	lastPoint = NULL;
	xcountour = 0;
	for (int i = 0; i < ps1.size(); i++) {
		Point* p = ps1[i];
		Point* p1 = ps2[i];
		int k = i + 1;
		if (k == ps1.size()) k = 0;
		Point* p2 = ps1[k];
		Point* p3 = ps2[k];
		Point a(p1->x-p->x,p1->y - p->y,p1->z - p->z);
		Point b(p2->x - p->x, p2->y - p->y, p2->z - p->z);
		Point n(a.y * b.z - b.y - a.z, -a.x * b.z + b.x * a.z, a.x * b.y - b.x * a.y);
		n.normolize();
		n.reverse();
		
		glNormal3d(n.x, n.y, n.z);
		glColor3d(0, 1, 0);
		Point* tx = getWallCoords(p);
		glTexCoord2d(tx->x, wall[1]);
		delete[] tx;
		glVertex3d(p1->x, p1->y, p1->z);
		tx = getWallCoords(p1);
		glTexCoord2d(tx->x, wall[3]);
		delete[] tx;
		glVertex3d(p->x, p->y, p->z);
		tx = getWallCoords(p2);
		glTexCoord2d(tx->x, wall[1]);
		delete[] tx;
		glVertex3d(p2->x, p2->y, p2->z);
		tx = getWallCoords(p3);
		glTexCoord2d(tx->x, wall[3]);
		delete[] tx;
		glVertex3d(p3->x, p3->y, p3->z);
		
	}
	glEnd();
}
void Designer::DrawCover(vector<Point*> ps)
{
	/*glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDepthMask(GL_FALSE);
	*/
	
	glBindTexture(GL_TEXTURE_2D, textureId);
	glBegin(GL_TRIANGLE_FAN);
	glNormal3d(0, 0, 1);
	Point* t = getCoverCoord(center.x, center.y);
	glColor4d(0, 1, 0, 0.5);
	glTexCoord3d(t->x, t->y, 0.5);
	delete[] t;
	glVertex3d(center.x, center.y, center.z+ps[0]->z);
	for (int i = 0; i < ps.size(); i++) {
		Point* p = ps[i];
		Point* t = getCoverCoord(p->x, p->y);
		glTexCoord2d(t->x, t->y);
		delete[] t;
		glVertex3d(p->x, p->y, p->z);
	}
	glEnd();
	glLoadIdentity();
}
void Designer::DrawCover1(vector<Point*> ps)
{
	glBindTexture(GL_TEXTURE_2D, textureId);
	glBegin(GL_TRIANGLE_FAN);
	glNormal3d(0, 0, -1);
	glColor3d(0, 1, 0);
	Point* t = getCoverCoord1(center.x, center.y);
	glTexCoord2d(t->x, t->y);
	delete[] t;
	glVertex3d(center.x, center.y, center.z + ps[0]->z);
	for (int i = 0; i < ps.size(); i++) {
		Point* p = ps[i];
		Point* t = getCoverCoord1(p->x, p->y);
		glTexCoord2d(t->x, t->y);
		delete[] t;
		glVertex3d(p->x, p->y, p->z);
	}
	glEnd();
}
void Designer::Draw()
{
	vector<Point*> ps1;
	vector<Point*> ps2;
	preInit();
	for (Point* p : points) {
		ps1.push_back(new Point(p->x,p->y,p->z));
	}
	DrawCover1(ps1);
	for (int i = 0; i < twists+1; i++) {
		double h = height * (i + 1) / (twists + 1);
		double a = angle * (i + 1) / (twists + 1);
		ps2 = ps1;
		ps1.clear();
		for (Point* p : points) {
			ps1.push_back((new Point(p->x, p->y, p->z+h))->rotate(a,&center));
		}
		DrawWalls(ps2,ps1);
	}
	DrawCover(ps1);
	for (Point* p : ps1) {
		delete[] p;
	}
	for (Point* p : ps2) {
		delete[] p;
	}

}
void Designer::SetTexture(int textureId, double width, double height) {
	this->textureId = textureId;
	size[0] = width;
	size[1] = height;
}
void Designer::CoverTexture(double x1, double y1, double x2, double y2) {
	cover[0] = x1 / size[0];
	cover[1] = y1 / size[1];
	cover[2] = x2 / size[0];
	cover[3] = y2 / size[1];
}
void Designer::Cover1Texture(double x1, double y1, double x2, double y2) {
	cover1[0] = x1 / size[0];
	cover1[1] = y1 / size[1];
	cover1[2] = x2 / size[0];
	cover1[3] = y2 / size[1];
}
void Designer::WallTexture(double x1, double y1, double x2, double y2) {
	wall[0] = x1 / size[0];
	wall[1] = y1 / size[1];
	wall[2] = x2 / size[0];
	wall[3] = y2 / size[1];
}
