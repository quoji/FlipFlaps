/*
Ruben Cardenas, Stephen Brownlee, Pedro Alvares
FlipFlaps.cpp
To be used with FlipFlaps
*/

#include "std_lib_facilities_4.h"
#include "Game_windows.h"
#include "Graph.h"
#include "GUI.h"

int main()
{
	Game_windows win(Point(100, 100), 1000, 800, "Flip Flaps!");
	cout << "I'm in main\n";
	
	return gui_main();
}