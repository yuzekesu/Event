#include "EventHandler.h"

EventHandler::EventHandler(std::function<void(void*)>&& event) {
	// Initialize shared resources
	_pID = new bool;
	_pIsKilling = new bool;
	_pLiving = new unsigned;
	_pEventHandler = new std::function<void(void*)>;

	// Set values
	IsLeader = true;
	*_pIsKilling = false;
	*_pLiving = 1;
	*_pEventHandler = event;
}

EventHandler::EventHandler(const EventHandler& copy) {
	// Copy over shared resources
	Copy(copy, false);
}

EventHandler::EventHandler(EventHandler&& move) noexcept {
	// Move over shared resources
	Copy(move, true);
	move.IsLeader = false;
}

EventHandler::~EventHandler() {
	// If leader, set Killing to true
	*_pIsKilling = IsLeader ? true : false;

	// Decrement living count and clean up if zero
	if (--(*_pLiving) < 1) {
		delete _pID;
		delete _pIsKilling;
		delete _pLiving;
		delete _pEventHandler;
	}
}

EventHandler& EventHandler::operator=(const EventHandler& copyAssign) {
	// Clean up current
	if (IsLeader) {
		*_pIsKilling = true;
	}
	(*_pLiving)--;
	// Copy over new with LeaderShip false.
	Copy(copyAssign, false);
	return *this;
}

EventHandler& EventHandler::operator=(EventHandler&& moveAssign) noexcept {
	// Clean up current
	if (IsLeader) {
		*_pIsKilling = true;
	}
	(*_pLiving)--;

	// Move over new with LeaderShip true.
	Copy(moveAssign, true);
	moveAssign.IsLeader = false;
	return *this;
}

bool EventHandler::operator==(const EventHandler& other) const {
	// Compare unique identity pointers
	return _pID == other._pID;
}

std::function<void(void*)>& EventHandler::Get() {
	return *_pEventHandler;
}

bool EventHandler::IsKilling() const {
	return *_pIsKilling;
}

void EventHandler::Copy(const EventHandler& other, bool copyLeadership) {
	_pID = other._pID;
	_pIsKilling = other._pIsKilling;
	_pLiving = other._pLiving;
	_pEventHandler = other._pEventHandler;
	IsLeader = copyLeadership ? other.IsLeader : false;
	(*_pLiving)++;
}