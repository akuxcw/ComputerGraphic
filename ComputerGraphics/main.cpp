#include "graph.h"
#include "button.h"
#include "curve.h"
#include "polygon.h"
#include "oval.h"
#include "line.h"
#include "circle.h"
#include "cube.h"

vector<Graph*> graph_table;
Color current_color;
Point clip_win1, clip_win2;

void init() {
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowPosition(960 - WINDOWWIDTH, 540 - WINDOWHEIGHT - 20);
	glutInitWindowSize(WINDOWWIDTH, WINDOWHEIGHT);
	glutCreateWindow("Graph System");

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glColor3f(0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, WINDOWWIDTH, 0, WINDOWHEIGHT);
	glFlush();
//	glutSwapBuffers();
}

void PressKeyboard(unsigned char key, int x, int y) {
	if (key == 27) { //ESC
		glDisable(GL_DEPTH_TEST);
		glDisable(GL_DITHER);

		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glColor3f(0.0, 0.0, 0.0);
		glClear(GL_COLOR_BUFFER_BIT);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluOrtho2D(0, WINDOWWIDTH, 0, WINDOWHEIGHT);
		glFlush();
		set_state(CHOOSE);
		Display();
	}
}
void PressSpecialKey(GLint key, GLint x, GLint y) {
	switch (key) {
	case GLUT_KEY_UP: AngleX -= 3.0f; break;
	case GLUT_KEY_DOWN: AngleX += 3.0f; break;
	case GLUT_KEY_LEFT: AngleY -= 3.0f; break;
	case GLUT_KEY_RIGHT: AngleY += 3.0f; break;
	}
	if (AngleX > 355.0f) AngleX = 0.0f;
	if (AngleX < 0.0f) AngleX = 355.0f;
	if (AngleY > 355.0f) AngleY = 0.0f;
	if (AngleY < 0.0f) AngleY = 355.0f;
	glutPostRedisplay();
}

void PressMouse(int key, int state, int x, int y) {
	y = WINDOWHEIGHT - y;
	switch (state) {
	case GLUT_DOWN:
		switch (key) {
		case GLUT_LEFT_BUTTON:
			for (int i = 0; i < (int)button_table.size(); ++ i) {
				if (button_table[i]->OnMouseDown(x, y)) {
					Display();
					return;
				}
			}
			if (get_state() < DrawGRAPH) DrawGraph(x, y);
			else ControlGraph(x, y);
			break;
		case GLUT_RIGHT_BUTTON:
			graph_table.clear();
			break;
		}
		break;
	case GLUT_UP:
		switch (key) {
		case GLUT_LEFT_BUTTON:
			for (int i = 0; i < (int)button_table.size(); ++ i) {
				button_table[i]->OnMouseUp();
			}
			for (int i = 0; i < (int)graph_table.size(); ++ i) {
				graph_table[i]->OnMouseUp();
			}
			switch (get_state()){
			case CLIP2:
				if (chosed_graph != NULL)chosed_graph->ClipGraph(clip_win1, clip_win2);
				clip_win1 = clip_win2;
				set_state(CLIP);
				break;
			case ROTATE2:
				set_state(ROTATE3);
				break;
			case SCALE2:
				set_state(SCALE3);
				break;
			case ROTATE3:
				if (chosed_graph != NULL)chosed_graph->UpdateAngle();
				break;
			}
			break;
		case GLUT_RIGHT_BUTTON:
			break;
		}
	}
	Display();

}

void MoveMouse(int x, int y) {
	if (graph_table.empty()) return;
	y = WINDOWHEIGHT - y;
	if (y > 500) return;
	
	if (get_state() < DrawGRAPH) {
		if (chosed_graph != NULL)chosed_graph->MovePoint(Point(x, y));
	}
	else switch(get_state()) {
	case CHOOSE:  if (chosed_graph != NULL)chosed_graph->MoveChosedPoint(x, y); break;
	case MOVE: if (chosed_graph != NULL)chosed_graph->MoveGraph(x, y); break;
	case ROTATE3: if (chosed_graph != NULL)chosed_graph->RotateGraph(x, y); break;
	case SCALE3: if (chosed_graph != NULL)chosed_graph->ScaleGraph(x, y); break;
	case CLIP2: clip_win2 = Point(x, y); break;
	}
	Display();
}

int main(int argc, char ** argv) {
	glutInit(&argc, argv);
	init_button();
	init();
	glutDisplayFunc(Display);
	glutKeyboardFunc(PressKeyboard);
	glutSpecialFunc(PressSpecialKey);
	glutMouseFunc(PressMouse);
	glutMotionFunc(MoveMouse);
	glutMainLoop();
	return 0;
}