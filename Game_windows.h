/*
Ruben Cardenas, Stephen Brownlee, Pedro Alvares
Game_windows.h
To be used with FlipFlaps
*/

#include "std_lib_facilities_4.h"
#include "Window.h"
#include "Graph.h"
#include "GUI.h"

using namespace Graph_lib;

struct Game_windows : Graph_lib::Window 
{
	Game_windows(Point xy, int w, int h, const string& title);
	
	private:
		Button play;			//Buttons for the main menu
		Button instructions;
		Button highscores;
		Button exit;
		Button menu_button;
		Button replay;
		In_box Initials;
		
		Button Ok;		//Button to go to the main menu
		Button enter;
		
		Button lvl_2;	//Button lvl selection
		Button lvl_3;
		Button lvl_4;
		Button lvl_5;
		Button lvl_6;
		Button lvl_7;
		Button lvl_8;
		Button lvl_9;

		void play_game();	//Functions called when buttons clicked
		void show_inst();
		void show_high();
		void exit_game();
		void enter_initials();
		void detach_menu();
		
		void make_file();
		void read_from_file();
		void write_to_file();
		
		void go_back();		//Function for 'Ok' button
		void game_go_back();
		
		void get_inst();		//used for the instructions
		void detach_inst();
		void attach_hard_menu();//show 1-9 buttons
		void detach_hard_menu();
		void detach_game();
		
		void do_replay();
		void main_title();
		void set_background();

		void set_difficulty(int i);
		int run_game(int p_cakes);
		void flip();
		void even_flip(int num_to_flip, int p_cakes, int midpoint);
		void odd_flip(int num_to_flip, int p_cakes, int midpoint);
		void handle_pancakes(int p_cakes, int pwidth, int wscaler, 
							int pancakeY, int table, int pheight);
		void generate_flip_buttons(int p_cakes, int pancakeY, int table, 
									int pheight, int flip_Y, int flip_X, 
									int flip_width,int flip_height);
		
		int calculate_score(int flips);
		void do_flip(int flip_id);
		void game_over();
		void you_win();
		void you_lose();
		
		void set_score(int num);
		string get_info(int which_one);
		void detach_scores();
		
		static void cb_play_game(Address, Address window);	//Callbacks for FLTK
		static void cb_show_inst(Address, Address window);
		static void cb_show_high(Address, Address window);
		static void cb_exit_game(Address, Address window);
		static void cb_enter_initials(Address, Address window);
		static void cb_replay(Address, Address window);
		
		static void cb_go_back(Address, Address window);
		static void cb_game_go_back(Address, Address window);

		static void cb_hard2(Address, Address pw);
		static void cb_hard3(Address, Address pw);
		static void cb_hard4(Address, Address pw);
		static void cb_hard5(Address, Address pw);
		static void cb_hard6(Address, Address pw);
		static void cb_hard7(Address, Address pw);
		static void cb_hard8(Address, Address pw);
		static void cb_hard9(Address, Address pw);

		static void cb_flip(Address, Address pw);
};

struct Flip_wrapper
{
	int id;
	Button* button_ptr;
};