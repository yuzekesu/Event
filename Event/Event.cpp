#include "Event.h"

void Event::Invoke(void* ptr) {
	for (auto i = _events.begin(); i != _events.end();) {
		if ((*i)->IsKilling()) {
			i = _events.erase(i);
		}
		else {
			(*i)->Get()(ptr);
			++i;
		}
	}
}

void Event::operator+=(const EventHandler& event) {
	_events.push_back(std::make_unique<EventHandler>(event));
}

void Event::operator-=(const EventHandler& event) {
	for (auto i = _events.begin(); i != _events.end();) {
		if (*(*i) == event) {
			i = _events.erase(i);
		}
		else {
			++i;
		}
	}
}