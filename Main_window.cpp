/*
Ruben Cardenas, Stephen Brownlee, Pedro Alvares
Main_window.cpp
To be used with FlipFlaps
*/

#include "std_lib_facilities_4.h"
#include "Main_window.h"
#include "Window.h"
#include "Graph.h"
#include "GUI.h"

using namespace Graph_lib;

Main_window::Main_window(Point xy, int w, int h, const string& title) :
	Window(xy, w, h, title),
	play(Point(x_max()-150,0), 50, 50, "Play", cb_play_game),
	instructions(Point(x_max()-70, 0), 50, 50, "Instructions", cb_show_inst),
	highscores(Point(x_max()-50, 0), 50, 50, "Highscores", cb_show_high),
	exit(Point(x_max()-50, y_max()-50), 50, 50, "Exit", cb_exit_game)
	{
		attach(play);
		attach(instructions);
		attach(highscores);
		attach(exit);
	}
	
void Main_window::play_game()
{
	cout << "Play the game";
}

void Main_window::show_inst()
{
	cout << "Show the instructions";
}

void Main_window::show_high()
{
	cout << "Show the highscores";
}

void Main_window::exit_game()
{
	cout << "Exit the game";
}

void Main_window::cb_play_game(Address, Address pw)
{
	reference_to<Main_window>(pw).play_game();
}

void Main_window::cb_show_inst(Address, Address pw)
{
	reference_to<Main_window>(pw).show_inst();
}

void Main_window::cb_show_high(Address, Address pw)
{
	reference_to<Main_window>(pw).show_high();
}

void Main_window::cb_exit_game(Address, Address pw)
{
	reference_to<Main_window>(pw).exit_game();
}