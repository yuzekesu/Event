#pragma once
#include <memory>
#include "EventHandler.h"

class Addition {
public:
	// Constructor to initialize the addition value
	Addition(int a);
	// Function call operator to add a value
	void operator()(int added);
	// Get the event handler that calls the addition operator
	EventHandler& Get_OnCallingEventHandler();
	// Get the current addition value
	int Get_Value() const;
private:
	int _a = 0;
	// constructor is called here.
	// Event handler that calls the addition operator
	EventHandler _OnCallingEventHandler = EventHandler([this](void* ptr) {this->operator()(1); });
};
