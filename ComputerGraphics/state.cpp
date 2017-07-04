#include "state.h"
#include "graph.h"

int _state = INIT;

int get_state() {
	return _state;
}

void set_state(int __state) {
	if (_state == ROTATE3 || _state == SCALE3) 
		if (chosed_graph != NULL)chosed_graph->UnsetRotateCenter();
	_state = __state;
}