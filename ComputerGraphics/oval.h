#ifndef __OVAL_H_
#define __OVAL_H_

#include "graph.h"

class Oval : public Graph {
private:
	Point center;//ÍÖÔ²ÖÐÐÄ
	int a, b;
public:
	Oval(Point a, Point b) {
		vertex.push_back(a);
		vertex.push_back(b);
		type = TYPEOVAL;
	}
	Oval() {
		type = TYPEOVAL;
	}
	void DrawP(int px, int py, int cx, int cy) {
		DrawPoint(px, py);
		if (px >= cx - 5 && px <= cx + 7 && py >= cy - 5 && py <= cy + 7) {
			SetChoose(this);
		}
	}

	void AddPoint(Point p) {
		printf("oval\n");
	}

	void MovePoint(Point p) {
		vertex[1] = p;
	}
	void DrawP_(int xx, int yy, int cx, int cy) {
		int x = center.x + (xx - center.x)*cos(angle) - (yy - center.y)*sin(angle);
		int y = center.y + (xx - center.x)*sin(angle) + (yy - center.y)*cos(angle);
		DrawP(x, y, cx, cy);
	}
	void DrawBackPoint_(int xx, int yy) {
		int x = center.x + (xx - center.x)*cos(angle) - (yy - center.y)*sin(angle);
		int y = center.y + (xx - center.x)*sin(angle) + (yy - center.y)*cos(angle);
		DrawBackPoint(x, y);
	}
	void Ellipsepot(int x0, int y0, int x, int y, int cx, int cy) {
		DrawP_((x0 + x), (y0 + y), cx, cy);
		DrawP_((x0 + x), (y0 - y), cx, cy);
		DrawP_((x0 - x), (y0 - y), cx, cy);
		DrawP_((x0 - x), (y0 + y), cx, cy);
	}
	void EllipsepotBack(int x0, int y0, int x, int y) {
		DrawBackPoint_((x0 + x), (y0 + y));
		DrawBackPoint_((x0 + x), (y0 - y));
		DrawBackPoint_((x0 - x), (y0 - y));
		DrawBackPoint_((x0 - x), (y0 + y));
	}
	void Draw(int cx, int cy) {
		center.x = (vertex[0].x + vertex[1].x) / 2;
		center.y = (vertex[0].y + vertex[1].y) / 2;

		Point start, end;
		start.x = center.x + (vertex[0].x - center.x)*cos(-angle) - (vertex[0].y - center.y)*sin(-angle);
		start.y = center.y + (vertex[0].x - center.x)*sin(-angle) + (vertex[0].y - center.y)*cos(-angle);
		end.x = center.x + (vertex[1].x - center.x)*cos(-angle) - (vertex[1].y - center.y)*sin(-angle);
		end.y = center.y + (vertex[1].x - center.x)*sin(-angle) + (vertex[1].y - center.y)*cos(-angle);

		a = abs(start.x - end.x) / 2;
		b = abs(start.y - end.y) / 2;

		int x0 = center.x;
		int y0 = center.y;
		double sqa = a*a;
		double sqb = b*b;
		double d = sqb + sqa*(0.25 - b);
		int x = 0;
		int y = b;
		if (isfilled) { //Ìî³ä
			for (int i = x; i <= y; ++ i) {
				EllipsepotBack(x0, y0, x, i);
			}
			for (int i = y; i <= x; ++ i) {
				EllipsepotBack(x0, y0, i, y);
			}
			while (sqb * (x + 1) < sqa * (y - 0.5)) {
				if (d < 0) d += sqb*(2 * x + 3);
				else {
					d += (sqb*(2 * x + 3) + sqa*((-2)*y + 2));
					-- y;
				}
				++ x;
				for (int i = x; i <= y; i++) EllipsepotBack(x0, y0, x, i);
				for (int i = y; i <= x; i++) EllipsepotBack(x0, y0, i, y);
			}
			d = (b * (x + 0.5)) * 2 + (a * (y - 1)) * 2 - (a * b) * 2;
			// 2
			while (y > 0) {
				if (d < 0) {
					d += sqb * (2 * x + 2) + sqa * ((-2) * y + 3);
					++ x;
				}
				else {
					d += sqa * ((-2) * y + 3);
				}
				-- y;
				for (int i = x; i <= y; ++ i) EllipsepotBack(x0, y0, x, i);
				for (int i = y; i <= x; ++ i) EllipsepotBack(x0, y0, i, y);
			}
		}
		d = sqb + sqa*(0.25 - b);
		x = 0;
		y = b;
		Ellipsepot(x0, y0, x, y, cx, cy);
		// 1
		while (sqb*(x + 1) < sqa*(y - 0.5)) {
			if (d < 0) {
				d += sqb*(2 * x + 3);
			}
			else {
				d += (sqb*(2 * x + 3) + sqa*((-2)*y + 2));
				--y ;
			}
			++ x;
			Ellipsepot(x0, y0, x, y, cx, cy);
		}
		d = (b * (x + 0.5)) * 2 + (a * (y - 1)) * 2 - (a * b) * 2;
		// 2
		while (y > 0) {
			if (d < 0) {
				d += sqb * (2 * x + 2) + sqa * ((-2) * y + 3);
				++x;
			}
			else {
				d += sqa * ((-2) * y + 3);
			}
			-- y;
			Ellipsepot(x0, y0, x, y, cx, cy);
		}
		AfterDraw();
		glFlush();
	}
};

#endif // !__OVAL_H