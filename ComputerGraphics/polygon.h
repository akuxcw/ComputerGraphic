#ifndef __POLYGON_H_
#define __POLYGON_H_

#include "graph.h"
#define winLeftBitCode 0x1
#define winRightBitCode 0x2
#define winBottomBitCode 0x4
#define winTopBitCode 0x8
enum { LEFT, RIGHT, BOTTOM, TOP };

struct Link
{
	float x;
	float dx, ymax;
	Link* next;
};
class MyPolygon : public Graph {
private :
public :
	MyPolygon(Point p) {
		this->vertex.push_back(p);
		type = TYPEPOLYGON;
	}
	MyPolygon() {
		type = TYPEPOLYGON;
	}
	void DrawP(int px, int py, int cx, int cy) {
		DrawPoint(px, py);
		if (px >= cx - 5 && px <= cx + 7 && py >= cy - 5 && py <= cy + 7) {
			SetChoose(this);
		}
	}

	void ShowControlPoints() {
		for (int i = 0; i < (int)vertex.size(); ++ i) {
			DrawControlPoint(vertex[i].x, vertex[i].y);
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
		} else {
			t = dx;
			dx = dy;
			dy = t;
			flag = 1;
		}
		h = 2 * dy - dx;
		for (int i = 1; i <= dx; ++ i) {
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

	void Draw(int cx, int cy) {
//		if (ishiden)
//			return;
		if (vertex.size() == 0)
			return;

		if (isfilled) {
			FillIn();
		}

//		setcolor();
		for (int i = 0; i < (int)vertex.size() - 1; ++ i) {
			Drawline(vertex[i], vertex[i + 1], cx, cy);
		}
		Drawline(vertex[vertex.size() - 1], vertex[0], cx, cy);
		AfterDraw();
		glFlush();
	}
	// begin fill
	void FillIn() {
		int POINTNUM = vertex.size();
		vector<fPoint> fvertex;
		for (int i = 0; i < POINTNUM; ++ i) {
			float x = vertex[i].x;
			float y = vertex[i].y;
			fPoint fp;
			fp.x = x;
			fp.y = y;
			fvertex.push_back(fp);
		}
		int MaxY, MinY;
		if (fvertex.size() >= 1) {
			MaxY = fvertex[0].y;
			MinY = fvertex[0].y;
		}
		for (int i = 0; i<POINTNUM; ++ i)
			if (fvertex[i].y>MaxY) MaxY = fvertex[i].y;

		for (int i = 0; i<POINTNUM; ++ i)
			if (fvertex[i].y<MinY) MinY = fvertex[i].y;

		if (MinY<0) {
			for (int i = 0; i < (int)fvertex.size(); i++) {
				fvertex[i].y -= MinY;
			}
			MaxY -= MinY;
		}
		Link *plinka = new Link;
		plinka->next = NULL;
		Link **plinkn = new Link*[MaxY * 2];
		for (int i = 0; i <= MaxY; ++ i) {
			plinkn[i] = new Link;
			plinkn[i]->next = NULL;
		}
		for (int i = 0; i <= MaxY; ++ i) {
			for (int j = 0; j < POINTNUM; ++ j)
				if (fvertex[j].y == i) {
					if (fvertex[(j - 1 + POINTNUM) % POINTNUM].y>fvertex[j].y) {
						Link *p = new Link;
						p->x = fvertex[j].x;
						p->ymax = fvertex[(j - 1 + POINTNUM) % POINTNUM].y;
						p->dx = (fvertex[(j - 1 + POINTNUM) % POINTNUM].x - fvertex[j].x) / (fvertex[(j - 1 + POINTNUM) % POINTNUM].y - fvertex[j].y);
						p->next = plinkn[i]->next;
						plinkn[i]->next = p;

					}
					if (fvertex[(j + 1 + POINTNUM) % POINTNUM].y>fvertex[j].y) {
						Link *p = new Link;
						p->x = fvertex[j].x;
						p->ymax = fvertex[(j + 1 + POINTNUM) % POINTNUM].y;
						p->dx = (fvertex[(j + 1 + POINTNUM) % POINTNUM].x - fvertex[j].x) / (fvertex[(j + 1 + POINTNUM) % POINTNUM].y - fvertex[j].y);
						p->next = plinkn[i]->next;
						plinkn[i]->next = p;
					}
				}
		}
		for (int i = 0; i <= MaxY; ++ i) {
			Link *p = plinka->next;
			while (p) {
				p->x = p->x + p->dx;
				p = p->next;
			}
			Link *tq = plinka;
			p = plinka->next;
			tq->next = NULL;
			while (p) {
				while (tq->next && p->x >= tq->next->x)
					tq = tq->next;
				Link *s = p->next;
				p->next = tq->next;
				tq->next = p;
				p = s;
				tq = plinka;
			}
			Link *q = plinka;
			p = q->next;
			while (p) {
				if (p->ymax == i) {
					q->next = p->next;
					delete p;
					p = q->next;
				} else {
					q = q->next;
					p = q->next;
				}
			}
			p = plinkn[i]->next;
			q = plinka;
			while (p) {
				while (q->next && p->x >= q->next->x) q = q->next;
				Link *s = p->next;
				p->next = q->next;
				q->next = p;
				p = s;
				q = plinka;
			}
			p = plinka->next;
			int yi = i;
			if (MinY<0) {
				yi += MinY;
			}
			while (p && p->next) {
				for (float j = p->x; j <= p->next->x; ++ j) {
					DrawBackPoint(static_cast<int>(j), yi);
				}
				p = p->next->next;
			}
		}
		glFlush();
	} 
	// end fill

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
	bool isPointinsideEdge(Point p, const int mode, Point win1, Point win2) {
		set_PointLoc(&p, win1, win2);
		switch (mode) {
		case LEFT:
			if ((p.loc & winLeftBitCode) == winLeftBitCode)return false;
			else return true;
		case RIGHT:
			if ((p.loc & winRightBitCode) == winRightBitCode)return false;
			else return true;
		case BOTTOM:
			if ((p.loc & winBottomBitCode) == winBottomBitCode)return false;
			else return true;
		case TOP:
			if ((p.loc & winTopBitCode) == winTopBitCode)return false;
			else return true;
		}
		return false;
	}
	bool isLinecrossEdge(Point p1, Point p2, const int mode, Point win1, Point win2) {
		if (isPointinsideEdge(p1, mode, win1, win2) == isPointinsideEdge(p2, mode, win1, win2))
			return false;
		return true;
	}
	Point intersect(Point p1, Point p2, const int mode, Point win1, Point win2) {
		int x_min, x_max, y_min, y_max;
		x_min = min(win1.x, win2.x);
		x_max = max(win1.x, win2.x);
		y_min = min(win1.y, win2.y);
		y_max = max(win1.y, win2.y);
		Point result;
		switch (mode) {
		case LEFT:
			result.x = x_min;
			result.y = p1.y + (x_min - p1.x) * (p2.y - p1.y) / (p2.x - p1.x);
			break;
		case RIGHT:
			result.x = x_max;
			result.y = p1.y + (x_max - p1.x) * (p2.y - p1.y) / (p2.x - p1.x);
			break;
		case BOTTOM:
			result.y = y_min;
			result.x = p1.x + (y_min - p1.y) / ((double)(p2.y - p1.y) / (double)(p2.x - p1.x));
			break;
		case TOP:
			result.y = y_max;
			result.x = p1.x + (y_max - p1.y) / ((double)(p2.y - p1.y) / (double)(p2.x - p1.x));
			break;
		}
		return result;
	}
	void parallelClip(Point p1, Point p2, vector<Point >* set, const int mode, Point win1, Point win2) {
		int x_min, x_max, y_min, y_max;
		x_min = min(win1.x, win2.x);
		x_max = max(win1.x, win2.x);
		y_min = min(win1.y, win2.y);
		y_max = max(win1.y, win2.y);
		if (p1.x == p2.x) {
			switch (mode) {
			case LEFT:
				if (p1.x >= x_min)set->push_back(p2);
				break;
			case RIGHT:
				if (p1.x <= x_max)set->push_back(p2);
				break;
			case BOTTOM:
				if ((p1.y >= y_min) && (p2.y >= y_min))	set->push_back(p2);
				else if ((p1.y >= y_min) && (p2.y < y_min)) {
					Point temp(p1.x, y_min);
					set->push_back(temp);
				}
				else if ((p1.y < y_min) && (p2.y >= y_min)) {
					Point temp(p1.x, y_min);
					set->push_back(temp);
					set->push_back(p2);
				}
				break;
			case TOP:
				if ((p1.y <= y_max) && (p2.y <= y_max))set->push_back(p2);
				else if ((p1.y > y_max) && (p2.y <= y_max)) {
					Point temp(p1.x, y_max);
					set->push_back(temp);
					set->push_back(p2);
				}
				else if ((p1.y <= y_max) && (p2.y > y_max)) {
					Point temp(p1.x, y_max);
					set->push_back(temp);
				}
				break;
			}
			return;
		}
		else if (p1.y == p2.y) {
			switch (mode) {
			case LEFT:
				if ((p1.x >= x_min) && (p2.x >= x_min))set->push_back(p2);
				else if ((p1.x < x_min) && (p2.x >= x_min)) {
					Point temp(x_min, p1.y);
					set->push_back(temp);
					set->push_back(p2);
				}
				else if ((p1.x >= x_min) && (p2.x < x_min)) {
					set->push_back(p1);
					Point temp(x_min, p1.y);
					set->push_back(temp);
				}
				break;
			case RIGHT:
				if ((p1.x <= x_max) && (p2.x <= x_max))set->push_back(p2);
				else if ((p1.x <= x_max) && (p2.x > x_max)) {
					set->push_back(p1);
					Point temp(x_max, p1.y);
					set->push_back(temp);
				}
				else if ((p1.x > x_max) && (p2.x <= x_max)) {
					Point temp(x_max, p1.y);
					set->push_back(temp);
					set->push_back(p2);
				}
				break;
			case BOTTOM:
				if (p1.y >= y_min)set->push_back(p2);
				break;
			case TOP:
				if (p1.y <= y_max)set->push_back(p2);
				break;
			}
			return;
		}
	}
	void PolygonEdgeClip(vector<Point>* set, vector<Point>* newset, const int mode, Point win1, Point win2) {
		for (auto pl = set->begin(); pl != set->end(); ++pl) {
			if (pl == (set->end() - 1)) break;
			auto pr = pl + 1;
			if (isPointinsideEdge(*pl, mode, win1, win2)) {
				if (isPointinsideEdge(*pr, mode, win1, win2)) {
					newset->push_back(*pr);
				}
				else {
					newset->push_back(intersect(*pl, *pr, mode, win1, win2));
				}
			}
			else if (!isPointinsideEdge(*pl, mode, win1, win2)) {
				if (isPointinsideEdge(*pr, mode, win1, win2)) {
					newset->push_back(intersect(*pl, *pr, mode, win1, win2));
					newset->push_back(*pr);
				}
			}
		}
		if (((set->end() - 1)->x == (set->begin())->x) || ((set->end() - 1)->y == (set->begin())->y))
			parallelClip(*(set->end() - 1), *(set->begin()), newset, mode, win1, win2);
		else if (isPointinsideEdge(*(set->end() - 1), mode, win1, win2)) {
			if (isPointinsideEdge(*(set->begin()), mode, win1, win2)) {
				newset->push_back(*(set->begin()));
			}
			else if (!isPointinsideEdge(*(set->begin()), mode, win1, win2)) {
				newset->push_back(intersect(*(set->end() - 1), *(set->begin()), mode, win1, win2));//
			}
		}
		else if (!isPointinsideEdge(*(set->end() - 1), mode, win1, win2)) {
			if (isPointinsideEdge(*(set->begin()), mode, win1, win2)) {
				newset->push_back(intersect(*(set->end() - 1), *(set->begin()), mode, win1, win2));
				newset->push_back(*(set->begin()));
			}
		}
	}
	void ClipGraph(Point win1, Point win2) {
		vector<Point> set_L, set_R, set_B, set_result;
		PolygonEdgeClip(&vertex, &set_L, LEFT, win1, win2);
		if (set_L.size() == 0) return;
		PolygonEdgeClip(&set_L, &set_R, RIGHT, win1, win2);
		if (set_R.size() == 0) return;
		PolygonEdgeClip(&set_R, &set_B, BOTTOM, win1, win2);
		if (set_B.size() == 0) return;
		PolygonEdgeClip(&set_B, &set_result, TOP, win1, win2);
		if (set_result.size() == 0) return;
		vertex = set_result;
	}
	//end clip
};

#endif // !__POLYGON_H_