/*
Ruben Cardenas, Stephen Brownlee, Pedro Alvares
Main_window.h
To be used with FlipFlaps
*/

#include "std_lib_facilities_4.h"
#include "Window.h"
#include "Graph.h"
#include "GUI.h"

using namespace Graph_lib;

struct Main_window : Graph_lib::Window 
{
	Main_window(Point xy, int w, int h, const string& title);
	
	private:
		Button play;
		Button instructions;
		Button highscores;
		Button exit;
		
		void play_game();
		void show_inst();
		void show_high();
		void exit_game();
		
		static void cb_play_game(Address, Address window);
		static void cb_show_inst(Address, Address window);
		static void cb_show_high(Address, Address window);
		static void cb_exit_game(Address, Address window);
};