#ifndef __GRAPH_H_
#define __GRAPH_H_
#include <gl/glut.h>
#include <windows.h>
#include <cstdio>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include "state.h"

#define WINDOWWIDTH 600
#define WINDOWHEIGHT 600
enum {TYPECIRCLE, TYPELINE, TYPEOVAL, TYPEPOLYGON, TYPECURVE};
using namespace std;
#define POINTSIZE 2.0f
class Color {
public :
	float x, y, z;
	Color(float x, float y, float z) {
		this->x = x;
		this->y = y;
		this->z = z;
	}
	Color() {
		this->x = 0;
		this->y = 0;
		this->z = 0;
	}
};
class Point {
public :
	int x, y;
	unsigned char loc;
	Point(int x, int y) {
		this->x = x;
		this->y = y;
	}
	Point() {
		this->x = 0;
		this->y = 0;
	}
};
class fPoint {
public:
	float x, y;
	fPoint(float x, float y) {
		this->x = x;
		this->y = y;
	}
	fPoint() {
		this->x = 0;
		this->y = 0;
	}
};

extern Color current_color;

class Graph {
protected:
	int type;
	int isfilled, ischosen;
	Color back, front;
	vector<Point> vertex, tmp_vertex;
	Point * chosed_point = NULL, * rotate_center = NULL;
	Point start;
	float angle, last_angle;
public:
	Graph() {
		last_angle = angle = 0;
		front = current_color;
		back = Color(1, 1, 1);
		isfilled = false;
		ischosen = false;
	}
	void print(FILE * fp) {
		fprintf(fp, "%d\n", type);
		fprintf(fp, "%d\n", isfilled);
		fprintf(fp, "%f %f %f %f %f %f\n", back.x, back.y, back.z, front.x, front.y, front.z);
		fprintf(fp, "%d", vertex.size());
		for (int i = 0; i < (int)vertex.size(); ++i) fprintf(fp, " %d %d", vertex[i].x, vertex[i].y);
		fprintf(fp, "\n");
		fprintf(fp, "%f %f\n", angle, last_angle);
	}
	void load(FILE * fp) {
		fscanf_s(fp, "%d", &isfilled);
		fscanf_s(fp, "%f %f %f %f %f %f", &back.x, &back.y, &back.z, &front.x, &front.y, &front.z);
		int n_vertex;
		fscanf_s(fp, "%d", &n_vertex);
		for (int i = 0; i < n_vertex; ++i) {
			Point p;
			fscanf_s(fp, "%d %d", &p.x, &p.y);
			vertex.push_back(p);
		}
		fscanf_s(fp, "%f %f", &angle, &last_angle);
	}
	void SetChosed() {
		ischosen = true;
	}
	void SetUnchosed() {
		ischosen = false;
	}
	void SetBackColor() {
		glColor3f(back.x, back.y, back.z);
	}
	void DrawPoint(int px, int py) {
		if (py > 500) return;
		glColor3f(front.x, front.y, front.z);//»­±ÊÑÕÉ«
		if(ischosen) glPointSize(POINTSIZE + 1); else glPointSize(POINTSIZE);//»­±Ê´ÖÏ¸
		glBegin(GL_POINTS);
		glVertex2i(px, py);//»­µã
		glEnd();		
	}
	void DrawBackPoint(int px, int py) {
		if (py > 500) return;
		glColor3f(back.x, back.y, back.z);//»­±ÊÑÕÉ«
		if (ischosen) glPointSize(POINTSIZE + 1); else glPointSize(POINTSIZE);//»­±Ê´ÖÏ¸
		glBegin(GL_POINTS);
		glVertex2i(px, py);//»­µã
		glEnd();
	}
	void DrawControlPoint(int px, int py) {
		if (py > 500) return;
		glColor3f(1.0, 0.0, 0.0);//»­±ÊÑÕÉ«
		if (ischosen) glPointSize(POINTSIZE + 5); else glPointSize(POINTSIZE);//»­±Ê´ÖÏ¸
		glBegin(GL_POINTS);
		glVertex2i(px, py);//»­µã
		glEnd();

	}
	void ShowControlPoints() {
		for (int i = 0; i < (int)vertex.size(); ++i) {
			DrawControlPoint(vertex[i].x, vertex[i].y);
		}
	}
	void SetChosedPoint(int x, int y) {
		for (int i = 0; i < (int)vertex.size(); ++i) {
			if (x >= vertex[i].x - 5 && x <= vertex[i].x + POINTSIZE + 5
				&& y >= vertex[i].y - 5 && y <= vertex[i].y + POINTSIZE + 5) {
				chosed_point = &vertex[i];
				break;
			}
		}
	}
	void AfterDraw() {
		if (ischosen) {
			ShowControlPoints();
		}
		if (rotate_center != NULL) {
			DrawControlPoint(rotate_center->x, rotate_center->y);
		}
	}
	void OnMouseUp() {
		chosed_point = NULL;
	}
	void MoveChosedPoint(int x, int y) {
		if (chosed_point == NULL) return;
		chosed_point->x = x;
		chosed_point->y = y;
	}
	void MoveGraph(int x, int y) {
		if (x < 0) {
			start = Point(-x, -y);
			tmp_vertex = vertex;
			return;
		}
		for (int i = 0; i < (int)vertex.size(); ++i) {
			vertex[i].x = tmp_vertex[i].x + x - start.x;
			vertex[i].y = tmp_vertex[i].y + y - start.y;
		}
	}
	void SetRotateCenter(int x, int y) {
		rotate_center = new Point(x, y);
	}
	void UnsetRotateCenter() {
		rotate_center = NULL;
	}
	void UpdateAngle() {
		last_angle = angle;
	}
	void RotateGraph(int x, int y) {
		if (x < 0) {
			start = Point(-x, -y);
			tmp_vertex = vertex;
			return;
		}
		int xx = start.x, yy = start.y;
		int xc1 = xx - rotate_center->x;
		int yc1 = yy - rotate_center->y;
		int x12 = x - xx;
		int y12 = y - yy;
		int xc2 = x - rotate_center->x;
		int yc2 = y - rotate_center->y;
		double cosa = (xc1*xc2 + yc1*yc2) / sqrt((pow(xc1, 2) + pow(yc1, 2))*(pow(xc2, 2) + pow(yc2, 2)));
		double sina = sqrt(1 - pow(cosa, 2));
		double angle_ = acos(cosa);
		if (xc1*y12 - yc1*x12 < 0) {
			sina = -sina;
			angle_ = 2 * acos(-1) - angle_;
		}
		angle = last_angle + angle_;
		while (angle > 2 * acos(-1)) angle -= 2 * acos(-1);
		for (int i = 0; i < (int)vertex.size(); ++i) {
			xx = tmp_vertex[i].x;
			yy = tmp_vertex[i].y;
			vertex[i].x = rotate_center->x + (xx - rotate_center->x)*cosa - (yy - rotate_center->y)*sina;
			vertex[i].y = rotate_center->y + (xx - rotate_center->x)*sina + (yy - rotate_center->y)*cosa;
		}
	}
	void ScaleGraph(int x, int y) {
		if (x < 0) {
			start = Point(-x, -y);
			tmp_vertex = vertex;
			return;
		}
		double dist1 = sqrt((x - rotate_center->x)*(x - rotate_center->x) + (y-rotate_center->y)*(y-rotate_center->y));
		double dist2 = sqrt((start.x - rotate_center->x)*(start.x - rotate_center->x) + (start.y - rotate_center->y)*(start.y - rotate_center->y));
		if (dist2 == 0) return;
		for (int i = 0; i < (int)vertex.size(); ++i) {
			vertex[i].x = (double)(tmp_vertex[i].x) * dist1 / dist2 + rotate_center->x * (1 - dist1 / dist2) + 0.5;
			vertex[i].y = (double)(tmp_vertex[i].y) * dist1 / dist2 + rotate_center->y * (1 - dist1 / dist2) + 0.5;
		}
	}
	void FillGraph() {
		isfilled = !isfilled;
		back = current_color;
	}
	virtual void DrawP(int, int, int, int) = 0;
	virtual void Draw(int, int) = 0;
	virtual void MovePoint(Point) = 0;
	virtual void AddPoint(Point) = 0;
	virtual void ClipGraph(Point, Point) {}
};

void SetChoose(Graph *);
void Display();
void DrawGraph(int, int);
void ControlGraph(int, int);
extern vector<Graph*> graph_table;
extern Graph * chosed_graph;
extern Point clip_win1, clip_win2;

#endif // !__GRAPH_H_
