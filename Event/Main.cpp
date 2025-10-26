#pragma once
#include <iostream>
#include <chrono>
#include "Event.h"
#include "Addition.h"

void Test_Event_Performance(int reps);
void Test_DirectCall_Performance(int reps);

int main() {
	Test_Event_Performance(1000000);
	Test_DirectCall_Performance(1000000);
	std::unique_ptr<Addition> add1 = std::make_unique<Addition>(0);
	Event event;
	event += add1->Get_OnCallingEventHandler();
	std::cout << "break" << std::endl;
	event += add1->Get_OnCallingEventHandler();
	std::cout << "break" << std::endl;
	event += add1->Get_OnCallingEventHandler();
	std::cout << "break" << std::endl;
	event += add1->Get_OnCallingEventHandler();
	event.Invoke();
	std::cout << "Addition Value: " << add1->Get_Value() << std::endl;
	add1.reset();
	event.Invoke();
}

void Test_Event_Performance(int reps) {
	Addition s(0);
	Addition t(0);
	Event event;
	for (int i = 0; i < reps; ++i) {
		event += s.Get_OnCallingEventHandler();
		event += t.Get_OnCallingEventHandler();
	}
	std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
	event.Invoke();
	std::cout << "Time for event       = " << (std::chrono::steady_clock::now() - start).count() << std::endl; // 0
}
void Test_DirectCall_Performance(int reps) {
	Addition s(0);
	Addition t(0);
	std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
	for (int i = 0; i < reps; ++i) {
		s(1);
		t(1);
	}
	std::cout << "Time for Direct Call = " << (std::chrono::steady_clock::now() - start).count() << std::endl; // 0
}