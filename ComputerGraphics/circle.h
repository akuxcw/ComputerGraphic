#ifndef __CIRCLE_H_
#define __CIRCLE_H_

#include "graph.h"

class Circle : public Graph{
private :
public :
	Circle(Point center, Point end) {
		vertex.push_back(center);
		vertex.push_back(end);
		type = TYPECIRCLE;
	}
	Circle() {
		type = TYPECIRCLE;
	}
	void DrawP(int px, int py, int cx, int cy) {
		DrawPoint(px, py);
		if (px >= cx - 5 && px <= cx + 7 && py >= cy - 5 && py <= cy + 7) {
			SetChoose(this);
		}
	}
	void AddPoint(Point p) {
		printf("circle\n");
	}

	void MovePoint(Point a) {
		vertex[1] = a;
	}
	void Cirpot(int x0, int y0, int x, int y, int cx, int cy) {
		DrawP((x0 + x), (y0 + y), cx, cy);
		DrawP((x0 + y), (y0 + x), cx, cy);
		DrawP((x0 + y), (y0 - x), cx, cy);
		DrawP((x0 + x), (y0 - y), cx, cy);
		DrawP((x0 - x), (y0 - y), cx, cy);
		DrawP((x0 - y), (y0 - x), cx, cy);
		DrawP((x0 - y), (y0 + x), cx, cy);
		DrawP((x0 - x), (y0 + y), cx, cy);
	}
	void CirpotBack(int x0, int y0, int x, int y) {
		DrawBackPoint((x0 + x), (y0 + y));
		DrawBackPoint((x0 + y), (y0 + x));
		DrawBackPoint((x0 + y), (y0 - x));
		DrawBackPoint((x0 + x), (y0 - y));
		DrawBackPoint((x0 - x), (y0 - y));
		DrawBackPoint((x0 - y), (y0 - x));
		DrawBackPoint((x0 - y), (y0 + x));
		DrawBackPoint((x0 - x), (y0 + y));
	}
	void Draw(int cx, int cy) {
		Point center = vertex[0];
		Point end = vertex[1];
		int radius = sqrt((center.x - end.x)*(center.x - end.x) + (center.y - end.y)*(center.y - end.y));
		int x0 = center.x;
		int y0 = center.y;
		int x = 0;
		int y = radius;
		int d = 1 - radius;
		Cirpot(x0, y0, x, y, cx, cy);
		//先假设以原点为圆心，再由原点移动到对应位置。
		while (x < y) {
			if (d < 0) {
				d += 2 * x + 3;
			}
			else {
				d += 2 * (x - y) + 5;
				y--;
			}
			x ++;
			if (isfilled) {
				for (int i = x; i <= y; i++) {
					CirpotBack(x0, y0, x, i);
				}
			}
			Cirpot(x0, y0, x, y, cx, cy);
		}
		AfterDraw();
		glFlush();
	}
};

#endif // !__CIRCLE_H_