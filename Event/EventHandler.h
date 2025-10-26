#pragma once
#include <functional>
#include <iostream>
#include <vector>

class EventHandler {
public:
	// Default constructor
	EventHandler() = delete;
	// Constructor that takes an rvalue reference to a function
	EventHandler(std::function<void(void*)>&& event);
	// Copy constructor
	EventHandler(const EventHandler& copy);
	// Move constructor
	EventHandler(EventHandler&& move)noexcept;
	// Destructor
	~EventHandler();
	// Copy assignment operator
	EventHandler& operator=(const EventHandler& other);
	// Move assignment operator
	EventHandler& operator=(EventHandler&& other) noexcept;
	// Equality operator
	bool operator==(const EventHandler& other) const;
	// Get the stored event handler function
	std::function<void(void*)>& Get();
	// Check if the leader is being destroyed
	bool IsKilling() const;
private:
	bool IsLeader; // Indicates if this instance is the leader of the shared resources
	bool* _pID; // Unique identity pointer
	bool* _pIsKilling; // Indicates if the leader is being destroyed
	unsigned* _pLiving; // Reference count
	std::function<void(void*)>* _pEventHandler; // The actual event handler function
	void Copy(const EventHandler& other, bool copyLeadership);
};
