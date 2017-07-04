#ifndef __LINE_H_
#define __LINE_H_
#include "graph.h"
class Line :public Graph{
private :
public :
	Line(Point start, Point end) {
		vertex.push_back(start);
		vertex.push_back(end);
		type = TYPELINE;
	}
	Line() {
		type = TYPELINE;
	}
	void DrawP(int px, int py, int cx, int cy) {
		DrawPoint(px, py);
		if (px >= cx - 5 && px <= cx + 7 && py >= cy - 5 && py <= cy + 7) {
			SetChoose(this);
		}
	}

	void AddPoint(Point p) {
		printf("line\n");
	}

	void MovePoint(Point x) {
		vertex[1] = x;
	}

	void Draw(int cx, int cy) {
		Point start = vertex[0];
		Point end = vertex[1];
		int x0 = start.x, y0 = start.y, x1 = end.x, y1 = end.y;
		if (x0 == x1 && y0 == y1) {
			DrawP(x0, y0, cx, cy);
		}
		int dx, dy, h, a, b, x, y, t;
		bool flag;
		dx = abs(x1 - x0);
		dy = abs(y1 - y0);
		if (x1 > x0) a = 1; else a = -1;
		if (y1 > y0) b = 1; else b = -1;
		x = x0;
		y = y0;
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
		for (int i = 1; i <= dx + 1; ++i) {
			DrawP(x, y, cx, cy);
			if (h >= 0) {
				if (!flag) y = y + b;
				else x = x + a;
				h = h - 2 * dx;
			}
			if (!flag) x = x + a;
			else y = y + b;
			h = h + 2 * dy;
		}
		AfterDraw();
		glFlush();
	}
	// begin clip
	void set_PointLoc(Point* pr, Point win1, Point win2) {
		int x_min, x_max, y_min, y_max;
		if (win1.x > win2.x) {
			x_min = win2.x;
			x_max = win1.x;
		}else {
			x_min = win1.x;
			x_max = win2.x;
		}
		if (win1.y > win2.y) {
			y_min = win2.y;
			y_max = win1.y;
		}else {
			y_min = win1.y;
			y_max = win2.y;
		}
		pr->loc = 0;
		if (pr->x < x_min)pr->loc |= winLeftBitCode;
		if (pr->x > x_max)pr->loc |= winRightBitCode;
		if (pr->y < y_min)pr->loc |= winBottomBitCode;
		if (pr->y > y_max)pr->loc |= winTopBitCode;
	}
	void set_Loc(vector<Point>* set, Point win1, Point win2) {
		for (auto pr = set->begin(); pr < set->end(); ++pr)set_PointLoc(&*pr, win1, win2);
	}
	void swapPoints(Point &p1, Point &p2) {
		Point _temp;
		_temp = p1;
		p1 = p2;
		p2 = _temp;
	}
	inline bool insideornot(Point p) {
		return !(p.loc);
	}
	inline unsigned char both_out(Point p1, Point p2) {
		return p1.loc & p2.loc;
	}
	inline unsigned char both_in(Point p1, Point p2) {
		return !(p1.loc | p2.loc);
	}
	void ClipGraph(Point win1, Point win2) {
		Point p1 = vertex[0];
		Point p2 = vertex[1];
		int x_min, x_max, y_min, y_max;
		if (win1.x > win2.x) {
			x_min = win2.x;
			x_max = win1.x;
		}else {
			x_min = win1.x;
			x_max = win2.x;
		}
		if (win1.y > win2.y) {
			y_min = win2.y;
			y_max = win1.y;
		}else {
			y_min = win1.y;
			y_max = win2.y;
		}
		bool done = false, plot = false;
		double m = 0;
		if (p1.x != p2.x)m = (float)(p2.y - p1.y) / (float)(p2.x - p1.x);
		while (!done) {
			set_PointLoc(&p1, win1, win2);
			set_PointLoc(&p2, win1, win2);
			if (both_in(p1, p2)) {
				done = true;
				plot = true;
			}else if (both_out(p1, p2)) {
				done = true;
			}else {
				if (insideornot(p1)) {
					swapPoints(p1, p2);
				}
				if (p1.loc & winLeftBitCode) {
					p1.y += (x_min - p1.x)*m;
					p1.x = x_min;
				}else if (p1.loc & winRightBitCode) {
					p1.y += (x_max - p1.x)*m;
					p1.x = x_max;
				}else if (p1.loc & winBottomBitCode) {
					if (p2.x != p1.x)
						p1.x += (y_min - p1.y) / m;
					p1.y = y_min;
				}else if (p1.loc & winTopBitCode) {
					if (p2.x != p1.x)
						p1.x += (y_max - p1.y) / m;
					p1.y = y_max;
				}
			}
		}
		if (plot) {
			vertex[0] = p1;
			vertex[1] = p2;
		}
	}
	// end clip
};

#endif // !__LINE_H_
