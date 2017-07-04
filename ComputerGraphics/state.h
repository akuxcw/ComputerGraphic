#ifndef __STATE_H_
#define __STATE_H_

enum{INIT, DrawLINE, DrawPOINT, DrawCIRCLE, DrawOVAL, 
	DrawPOLYGON, DrawPOLYGON2, DrawCURVE, DrawCURVE2, DrawCUBE, DrawGRAPH, 
	CHOOSE, MOVE, ROTATE, ROTATE2, ROTATE3, FILL, DELETE_, CLIP, CLIP2, 
	SCALE, SCALE2, SCALE3};

int get_state();
void set_state(int);

#endif // !__STATE_H_
