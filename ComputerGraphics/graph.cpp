#include "graph.h"
#include "button.h"
#include "curve.h"
#include "polygon.h"
#include "oval.h"
#include "line.h"
#include "circle.h"
#include "cube.h"
Graph * chosed_graph;
void SetChoose(Graph * g) {
	for (int i = 0; i < (int)graph_table.size(); ++i) {
		graph_table[i]->SetUnchosed();
	}
	g->SetChosed();
	chosed_graph = g;
}
void DrawGraph(int x, int y) {
	if (y > 500) return;
	Graph * tmp;
	Point a, b;
	switch (get_state()) {
	case DrawPOLYGON:
		tmp = new MyPolygon(Point(x, y));
		SetChoose(tmp);
		graph_table.push_back(tmp);
		graph_table.back()->AddPoint(Point(x, y));
		set_state(DrawPOLYGON2);
		break;
	case DrawPOLYGON2:
		graph_table.back()->AddPoint(Point(x, y));
		break;
	case DrawCURVE:
		tmp = new Curve(Point(x, y));
		SetChoose(tmp);
		graph_table.push_back(tmp);
		graph_table.back()->AddPoint(Point(x, y));
		set_state(DrawCURVE2);
		break;
	case DrawCURVE2:
		graph_table.back()->AddPoint(Point(x, y));
		break;
	case DrawLINE:
		a.x = x, a.y = y;
		tmp = new Line(a, a);
		SetChoose(tmp);
		graph_table.push_back(tmp);
		break;
	case DrawCIRCLE:
		a.x = x, a.y = y;
		tmp = new Circle(a, a);
		SetChoose(tmp);
		graph_table.push_back(tmp);
		break;
	case DrawOVAL:
		a.x = x, a.y = y;
		tmp = new Oval(a, a);
		SetChoose(tmp);
		graph_table.push_back(tmp);
		break;
	default: break;
	}
}

void ControlGraph(int x, int y) {
	switch (get_state()) {
	case CHOOSE:
		if (chosed_graph != NULL) {
			chosed_graph->SetUnchosed();
			chosed_graph = NULL;
		}
		for (int i = 0; i < (int)graph_table.size(); ++i) {
			graph_table[i]->Draw(x, y);
		}
		if(chosed_graph != NULL)chosed_graph->SetChosedPoint(x, y);
		break;
	case MOVE:
		if (chosed_graph != NULL)chosed_graph->MoveGraph(-x, -y);
		break;
	case ROTATE:
		if (chosed_graph != NULL)chosed_graph->SetRotateCenter(x, y);
		set_state(ROTATE2);
		break;
	case SCALE:
		if (chosed_graph != NULL)chosed_graph->SetRotateCenter(x, y);
		set_state(SCALE2);
		break;
	case ROTATE3:
		if (chosed_graph != NULL)chosed_graph->RotateGraph(-x, -y);
		break;
	case SCALE3:
		if (chosed_graph != NULL)chosed_graph->ScaleGraph(-x, -y);
		break;
	case CLIP:
		clip_win1 = clip_win2 = Point(x, y);
		set_state(CLIP2);
		break;
	default: break;
	}
}

void Display() {
//	printf("Display\n");
	glClear(GL_COLOR_BUFFER_BIT);
	if (get_state() == CLIP2) {
		glColor3f(0.5, 1, 1);
		glBegin(GL_POLYGON);
		glVertex2i(clip_win1.x, clip_win1.y);
		glVertex2i(clip_win1.x, clip_win2.y);
		glVertex2i(clip_win2.x, clip_win2.y);
		glVertex2i(clip_win2.x, clip_win1.y);
		glEnd();
	}
	if (get_state() == DrawCUBE) {
		ShowCube();
	}
	else {
		for (int i = 0; i < (int)graph_table.size(); ++i) {
			graph_table[i]->Draw(-1, -1);
		}
		for (int i = 0; i < (int)button_table.size(); ++i) {
			button_table[i]->Display();
		}
		glColor3f(current_color.x, current_color.y, current_color.z);
		glRectf(560, 568, 590, 538);

	}
	glFlush();
	glutSwapBuffers();
}
