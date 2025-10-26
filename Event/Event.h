#pragma once
#include <iostream>
#include <functional>
#include <memory>
#include <vector>
#include "EventHandler.h"

class Event {
public:
	// Invoke all event handlers with an optional pointer argument
	void Invoke(void* ptr = nullptr);
	// Add or remove event handlers
	void operator+=(const EventHandler& event);
	void operator-=(const EventHandler& event);
private:
	// Store event handlers
	std::vector<std::unique_ptr<EventHandler>> _events;
};
