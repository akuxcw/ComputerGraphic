#ifndef __CURVE_H_
#define __CURVE_H_

#include "graph.h"
#define NODENUM 20

class Curve : public Graph{
private:
public:
	Curve(Point p) {
		this->vertex.push_back(p);
		type = TYPECURVE;
	}
	Curve() {
		type = TYPECURVE;
	}
	void DrawP(int px, int py, int cx, int cy) {
		DrawPoint(px, py);
		if (px >= cx - 5 && px <= cx + 7 && py >= cy - 5 && py <= cy + 7) {
			SetChoose(this);
		}
	}
	void DrawControlP(int px, int py, int cx, int cy) {
		if (px >= cx - 5 && px <= cx + 7 && py >= cy - 5 && py <= cy + 7) {
			SetChoose(this);
		}
		if (ischosen) {
			if (py > 500) return;
			glColor3f(front.x, front.y, front.z);//»­±ÊÑÕÉ«
			glPointSize(POINTSIZE-1);//»­±Ê´ÖÏ¸
			glBegin(GL_POINTS);
			glVertex2i(px, py);//»­µã
			glEnd();
		}
	}
	void MovePoint(Point p) {
		vertex.back() = p;
	}
	void AddPoint(Point p) {
		vertex.push_back(p);
	}
	void Drawline(Point p1, Point p2, int cx, int cy) {
		int x0 = p1.x, y0 = p1.y, x1 = p2.x, y1 = p2.y;
		if (x0 == x1&&y0 == y1) {
			DrawP(x0, y0, cx, cy);
		}
		int dx, dy, h, a, b, x, y, flag, t;
		dx = abs(x1 - x0); dy = abs(y1 - y0);
		if (x1 > x0) a = 1; else a = -1;
		if (y1 > y0) b = 1; else b = -1;
		x = x0; y = y0;
		if (dx >= dy) {
			flag = 0;
		}
		else {
			t = dx;
			dx = dy;
			dy = t;
			flag = 1;
		}
		h = 2 * dy - dx;
		for (int i = 1; i <= dx; ++i) {
			DrawP(x, y, cx, cy);
			if (h >= 0) {
				if (flag == 0) y = y + b;
				else x = x + a;
				h = h - 2 * dx;
			}
			if (flag == 0) x = x + a;
			else y = y + b;
			h = h + 2 * dy;
		}
	}
	void DrawControlline(Point p1, Point p2, int cx, int cy) {
		int x0 = p1.x, y0 = p1.y, x1 = p2.x, y1 = p2.y;
		if (x0 == x1&&y0 == y1) {
			DrawControlP(x0, y0, cx, cy);
		}
		int dx, dy, h, a, b, x, y, flag, t;
		dx = abs(x1 - x0); dy = abs(y1 - y0);
		if (x1 > x0) a = 1; else a = -1;
		if (y1 > y0) b = 1; else b = -1;
		x = x0; y = y0;
		if (dx >= dy) {
			flag = 0;
		}
		else {
			t = dx;
			dx = dy;
			dy = t;
			flag = 1;
		}
		h = 2 * dy - dx;
		for (int i = 1; i <= dx; ++i) {
			DrawControlP(x, y, cx, cy);
			if (h >= 0) {
				if (flag == 0) y = y + b;
				else x = x + a;
				h = h - 2 * dx;
			}
			if (flag == 0) x = x + a;
			else y = y + b;
			h = h + 2 * dy;
		}
	}
	//»­ÇúÏß
	void Drawcurve(int cx, int cy) {
		if (vertex.size() < 4) return;
		float f1, f2, f3, f4;
		float deltaT = 1.0 / NODENUM;
		float T;
		vector<Point> astring;
		for (int num = 0; num < (int)vertex.size() - 3; num++) {
			for (int i = 0; i <= NODENUM; i++) {
				T = i * deltaT;
				//ËÄ¸ö»ùº¯ÊýµÄÖµ
				f1 = (-T*T*T + 3 * T*T - 3 * T + 1) / 6.0;
				f2 = (3 * T*T*T - 6 * T*T + 4) / 6.0;
				f3 = (-3 * T*T*T + 3 * T*T + 3 * T + 1) / 6.0;
				f4 = (T*T*T) / 6.0;
				Point p(f1*vertex[num].x + f2*vertex[num + 1].x + f3*vertex[num + 2].x + f4*vertex[num + 3].x,
					f1*vertex[num].y + f2*vertex[num + 1].y + f3*vertex[num + 2].y + f4*vertex[num + 3].y);
				astring.push_back(p);
			}
		}

		for (int i = 0; i < (int)astring.size() - 1; i++) {
			Drawline(astring[i], astring[i + 1], cx, cy);
		}
	}
	void DrawControlPolygon(int cx, int cy) {
		glColor3f(1.0, 1.0, 1.0);//»­±ÊÑÕÉ«
		glPointSize(1.0f);//»­±Ê´ÖÏ¸
		for (int i = 0; i < vertex.size() - 1; i++) {
			DrawControlline(vertex[i], vertex[i + 1], cx, cy);
		}
	}
	void Draw(int cx, int cy) {
		if (vertex.size() == 0) return;
		Drawcurve(cx, cy);
		DrawControlPolygon(cx, cy);
		AfterDraw();
		glFlush();
	}
};

#endif // !__CURVE_H_