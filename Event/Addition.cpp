#include "Addition.h"

Addition::Addition(int a) {
	_a = a;
}

void Addition::operator()(int added) {
	_a += added;
}

EventHandler& Addition::Get_OnCallingEventHandler() {
	return _OnCallingEventHandler;
}

int Addition::Get_Value() const {
	return _a;
}