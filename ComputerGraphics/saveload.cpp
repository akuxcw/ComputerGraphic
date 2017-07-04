#include "saveload.h"
#include "graph.h"
#include "curve.h"
#include "polygon.h"
#include "oval.h"
#include "line.h"
#include "circle.h"
#include <time.h>

void SaveAsJpg() {
	unsigned char *mpixels = new unsigned char[WINDOWWIDTH * WINDOWHEIGHT * 3];
	glReadBuffer(GL_FRONT);
	glReadPixels(0, 0, WINDOWWIDTH, WINDOWHEIGHT, GL_RGB, GL_UNSIGNED_BYTE, mpixels);
	glReadBuffer(GL_BACK);
	for (int i = 0; i < (int)WINDOWWIDTH*WINDOWHEIGHT * 3; i += 3) {
		mpixels[i] ^= mpixels[i + 2] ^= mpixels[i] ^= mpixels[i + 2];
	}
	FIBITMAP* bitmap = FreeImage_Allocate(WINDOWWIDTH, WINDOWHEIGHT - 100, 24, 8, 8, 8);

	for (int y = 0; y < (int)FreeImage_GetHeight(bitmap); ++y) {
		BYTE *bits = FreeImage_GetScanLine(bitmap, y);
		for (int x = 0; x < (int)FreeImage_GetWidth(bitmap); ++x) {
			bits[0] = mpixels[(y*WINDOWWIDTH + x) * 3 + 0];
			bits[1] = mpixels[(y*WINDOWWIDTH + x) * 3 + 1];
			bits[2] = mpixels[(y*WINDOWWIDTH + x) * 3 + 2];
			bits += 3;
		}

	}
	FreeImage_Save(FIF_JPEG, bitmap, "graph.jpg", JPEG_DEFAULT);

	FreeImage_Unload(bitmap);
}

void Save() {
	FILE * fp;
	fopen_s(&fp, "graph.cg", "w");
	for (int i = 0; i < (int)graph_table.size(); ++i) {
		graph_table[i]->print(fp);
	}
	fclose(fp);
}

void Load() {
	clock_t st = clock();
	int type;
	graph_table.clear();
	FILE * fp;
	fopen_s(&fp, "graph.cg", "r");
	while (fscanf_s(fp, "%d", &type) != -1) {
		Circle * p1 = new Circle;
		Curve * p2 = new Curve;
		Line * p3 = new Line;
		Oval * p4 = new Oval;
		MyPolygon * p5 = new MyPolygon;
		switch (type) {
		case TYPECIRCLE:
			p1->load(fp);
			graph_table.push_back(p1);
			break;
		case TYPECURVE:
			p2->load(fp);
			graph_table.push_back(p2);
			break;
		case TYPELINE:
			p3->load(fp);
			graph_table.push_back(p3);
			break;
		case TYPEOVAL:
			p4->load(fp);
			graph_table.push_back(p4);
			break;
		case TYPEPOLYGON:
			p5->load(fp);
			graph_table.push_back(p5);
			break;
		}
	}
	Display();
	fclose(fp);
	printf("%d\n", (int)(clock() - st));
}