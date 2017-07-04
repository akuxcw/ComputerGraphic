#include "button.h"
#include "state.h"
#include "cube.h"
#include "saveload.h"

vector<Button *> button_table;
extern Color current_color;
Color color;
void Draw_line() {
	set_state(DrawLINE);
}
void Draw_circle() {
	set_state(DrawCIRCLE);
}
void Draw_oval() {
	set_state(DrawOVAL);
}
void DrawPolygon() {
	set_state(DrawPOLYGON);
}
void Draw_curve() {
	set_state(DrawCURVE);
}
void Draw_cube() {
	set_state(DrawCUBE);
	CubeInit();
}
void choose() {
	set_state(CHOOSE);
}
void move() {
	set_state(MOVE);
}
void rotate() {
	set_state(ROTATE);
}
void scale() {
	set_state(SCALE);
}
void fill() {
	set_state(FILL);
	if(chosed_graph != NULL)chosed_graph->FillGraph();
}
void Delete() {
	if (get_state() == DELETE_) {
		graph_table.clear();
		return;
	}
	set_state(DELETE_);
	if (graph_table.empty() || chosed_graph == NULL) return;
	for (int i = 0; i < (int)graph_table.size(); ++ i) {
		if ((int)graph_table[i] == (int)chosed_graph) {
			graph_table.erase(graph_table.begin() + i);
			break;
		}
	}
}
void clip() {
	set_state(CLIP);
}

#define ColorButtonR(yy); \
	auto funcR##yy = []() {current_color.x = yy / 10.0; }; \
	pBtn = new Button(450 + yy * 9, 560, 9, 15, Color(yy / 10.0, 0, 0), Color(0, 0, 0), "", funcR##yy);\
	button_table.push_back(pBtn);
#define ColorButtonG(yy); \
	auto funcG##yy = []() {current_color.y = yy / 10.0; }; \
	pBtn = new Button(450 + yy * 9, 545, 9, 15, Color(0, yy / 10.0, 0), Color(0, 0, 0), "", funcG##yy);\
	button_table.push_back(pBtn);
#define ColorButtonB(yy); \
	auto funcB##yy = []() {current_color.z = yy / 10.0; }; \
	pBtn = new Button(450 + yy * 9, 530, 9, 15, Color(0, 0, yy / 10.0), Color(0, 0, 0), "", funcB##yy);\
	button_table.push_back(pBtn);

void init_button() {
	//»­Í¼ÐÎ
	Color back(0, 1, 1);
	Button * pBtn = new Button(10, 560, 30, 15, back, Color(0, 0, 0), "Line", Draw_line);
	button_table.push_back(pBtn);
	pBtn = new Button(60, 560, 40, 15, back, Color(0, 0, 0), "Circle", Draw_circle);
	button_table.push_back(pBtn);
	pBtn = new Button(120, 560, 30, 15, back, Color(0, 0, 0), "Oval", Draw_oval);
	button_table.push_back(pBtn);
	pBtn = new Button(170, 560, 50, 15, back, Color(0, 0, 0), "Polygon", DrawPolygon);
	button_table.push_back(pBtn);
	pBtn = new Button(240, 560, 40, 15, back, Color(0, 0, 0), "Curve", Draw_curve);
	button_table.push_back(pBtn);
	pBtn = new Button(300, 560, 34, 15, back, Color(0, 0, 0), "Cube", Draw_cube);
	button_table.push_back(pBtn);
	//±à¼­Í¼ÐÎ
	back = Color(1, 1, 0);
	pBtn = new Button(10, 530, 50, 15, back, Color(0, 0, 0), "Choose", choose);
	button_table.push_back(pBtn);
	pBtn = new Button(70, 530, 35, 15, back, Color(0, 0, 0), "Move", move);
	button_table.push_back(pBtn);
	pBtn = new Button(115, 530, 22, 15, back, Color(0, 0, 0), "Fill", fill);
	button_table.push_back(pBtn);
	pBtn = new Button(147, 530, 50, 15, back, Color(0, 0, 0), "Rotate", rotate);
	button_table.push_back(pBtn);
	pBtn = new Button(207, 530, 25, 15, back, Color(0, 0, 0), "Del", Delete);
	button_table.push_back(pBtn);
	pBtn = new Button(243, 530, 25, 15, back, Color(0, 0, 0), "Clip", clip);
	button_table.push_back(pBtn);
	pBtn = new Button(278, 530, 37, 15, back, Color(0, 0, 0), "Scale", scale);
	button_table.push_back(pBtn);
	//¶ÁÈ¡±£´æ
	back = Color(0, 0, 0.5);
	pBtn = new Button(350, 570, 90, 15, back, Color(1, 1, 1), " Save as Jpg", SaveAsJpg);
	button_table.push_back(pBtn);
	pBtn = new Button(350, 545, 90, 15, back, Color(1, 1, 1), " Save ", Save);
	button_table.push_back(pBtn);
	pBtn = new Button(350, 520, 90, 15, back, Color(1, 1, 1), " Load ", Load);
	button_table.push_back(pBtn);
	//ÑÕÉ«
	ColorButtonR(0); ColorButtonG(0); ColorButtonB(0);
	ColorButtonR(1); ColorButtonG(1); ColorButtonB(1);
	ColorButtonR(2); ColorButtonG(2); ColorButtonB(2);
	ColorButtonR(3); ColorButtonG(3); ColorButtonB(3);
	ColorButtonR(4); ColorButtonG(4); ColorButtonB(4);
	ColorButtonR(5); ColorButtonG(5); ColorButtonB(5);
	ColorButtonR(6); ColorButtonG(6); ColorButtonB(6);
	ColorButtonR(7); ColorButtonG(7); ColorButtonB(7);
	ColorButtonR(8); ColorButtonG(8); ColorButtonB(8);
	ColorButtonR(9); ColorButtonG(9); ColorButtonB(9);
	ColorButtonR(10); ColorButtonG(10); ColorButtonB(10);

}