/*
Ruben Cardenas, Stephen Brownlee, Pedro Alvarez
Game_windows.cpp
To be used with FlipFlaps
*/

#include "std_lib_facilities_4.h"
#include "Game_windows.h"
#include "Window.h"
#include "Graph.h"
#include "GUI.h"
#include "find_solution.h"
#include "High_scores.h"

//----------------------------------------------------------------------------

using namespace Graph_lib;

int width = 500;		//size for home page buttons
int height = 100;

int offset = 80;
int diff_width = 80;
int diff_height = 50;

int num_flips = 0;
int score = 0, num_arranged = 0;

string player_name = "";

fstream scores;

Color maroon(fl_rgb_color(80, 0, 0));
Color brown(fl_rgb_color(153, 102, 51));
Color brown_trim(fl_rgb_color(255, 222, 176));
Color dark_brown(fl_rgb_color(176,102,5));
Color light_brown(fl_rgb_color(217,140,33));

vector<Flip_wrapper> flip_info;  
vector<Rectangle*> pancakes;
vector<Line*> lines;
vector<int> widths, *solution;
vector<High_scores> player_scores;

Image main_screen(Point(0, 0), "FlipFlaps.jpg");
Image trophy(Point(300,150),"winner.gif");
Image defeat(Point(400,250),"defeat.gif");

Rectangle back_for_now(Point(0, 0), x_max(), y_max());
Rectangle tabletop(Point(250,800-250), 500, 80); 
Rectangle tableleg(Point(275,800-250), 50, 200);
Rectangle tableleg2(Point(675,800-250), 50, 200);

Text score_1(Point (400, 100), "");
Text score_2(Point(400, 200), "");
Text score_3(Point(400, 300), "");
Text score_4(Point(400, 400), "");
Text score_5(Point(400, 500), "");
Text inst_1(Point(x_max() / 2 - 40, 100), "");
Text inst_2(Point(50, 140), "");
Text inst_3(Point(50, 180), "");
Text inst_4(Point(50, 220), "");
Text inst_5(Point(50, 260), "");
Text inst_6(Point(50, 300), "");
Text inst_7(Point(50, 340), "");
Text inst_8(Point(50, 380), "");
Text inst_9(Point(50, 420), "");
//Text game_title(Point(400, 100), "");
Text no_high(Point(300, 100), "");
Text you_win_txt(Point(260, 140), "");
Text you_lose_txt(Point(400, 200), "");
Text your_score(Point(50,50),"");
Text flips_to_win(Point(50,100),"");
Text lvl_diff(Point(380,485), ""); 
Text username(Point(430, 200), "");


bool sort_scores(High_scores &sc_1, High_scores &sc_2)
{
	return sc_1.get_score() > sc_2.get_score();
}

Game_windows::Game_windows(Point xy, int w, int h, const string& title) :
	Window(xy, w, h, title),
	play(Point((x_max() / 2 - width / 2 + 20), 330), width-100, height-30, "Play", cb_play_game),
	instructions(Point((x_max() / 2 - width / 2 + 20), 430), width-100, height-30, "Instructions", cb_show_inst),
	highscores(Point((x_max() / 2 - width / 2 + 20), 530), width-100, height-30, "Highscores", cb_show_high),
	exit(Point((x_max() / 2 - width / 2 + 20), 630), width-100, height-30, "Exit", cb_exit_game),
	Ok(Point((x_max() / 2 - width / 2 + 50), 600), width-100, height-30, "Return To Menu", cb_go_back),
	replay(Point(400+(x_max() / 2 - width / 2), 600), width / 2, height, "Play Again", cb_replay),
	menu_button(Point((x_max() / 2 - width / 2)-100, 600), width / 2, height, "Main Menu", cb_game_go_back),
	enter(Point(530, 220), 100, 50, "Enter", cb_enter_initials),
	Initials(Point(430,220), 100,50, ""),
	lvl_2(Point(100+offset*1,500), diff_width, diff_height, "2", cb_hard2),
	lvl_3(Point(100+offset*2,500), diff_width, diff_height, "3", cb_hard3),
	lvl_4(Point(100+offset*3,500), diff_width, diff_height, "4", cb_hard4),
	lvl_5(Point(100+offset*4,500), diff_width, diff_height, "5", cb_hard5),
	lvl_6(Point(100+offset*5,500), diff_width, diff_height, "6", cb_hard6),
	lvl_7(Point(100+offset*6,500), diff_width, diff_height, "7", cb_hard7),
	lvl_8(Point(100+offset*7,500), diff_width, diff_height, "8", cb_hard8),
	lvl_9(Point(100+offset*8,500), diff_width, diff_height, "9", cb_hard9)
	{
		attach(Initials);
		attach(main_screen);
		attach(play);			//Shows all of the buttons for the main menu
		attach(instructions);
		attach(highscores);
		attach(exit);
		
		attach_hard_menu();
		attach(enter);
		
		detach(enter);
		detach(Initials);
		detach_hard_menu();
		
		main_title();
	}
	
void Game_windows::play_game()
{
	cout << "Play the game\n";		//Used for button testing for now
	
	username.set_label("Enter Initials");
	username.set_font_size(30);
	lvl_diff.set_label("Select Difficulty");
	lvl_diff.set_font_size(30);
	
	//detach(game_title);
	detach_menu();
	detach(back_for_now);
	
	attach(Initials);
	attach(enter);
	set_background();
	attach(lvl_diff); 
	attach(username);
	
	attach_hard_menu();
	attach(Ok);
}

void Game_windows::show_inst()			//Goes to instruction page when button clicked
{
	cout << "Show the instructions\n";
	
	detach_menu();
	//detach(game_title);
	detach(back_for_now);
	
	set_background();
	get_inst();
	attach(Ok);
}

void Game_windows::show_high()		//Goes to highscores page when button clicked
{
	cout << "Show the highscores\n";
	
	detach_menu();
	//detach(game_title);
	detach(back_for_now);
	
	set_background();
	attach(Ok);
	
	no_high.set_label("No Highscores Yet");
	no_high.set_font_size(50);
	
	scores.open("Scores.txt", ios::in);
	
	if (!scores.is_open())
	{
		make_file();
		
		attach(no_high);
	}
	
	else
		read_from_file();
}

void Game_windows::make_file()
{
	scores.clear();
	scores.open("Scores.txt", ios::out);
	scores.close();
	scores.open("Scores.txt", ios::in);
	scores.close();
		
	cout << "File created\n";
}

void Game_windows::read_from_file()
{
	string initials;
	int points, length;
	
	initials = "";
	points = 0;
	
	cout << "File is open\n";
		
	scores.seekg(0, ios::end);
		
	length = scores.tellg();
		
	if (length == 0)
	{
		cout << "Blah\n";
		attach(no_high);
	}
	
	else
	{
		scores.seekg(0);
		
		if (!scores.eof())
		{
			while (!scores.eof())
			{
				scores >> initials >> points;
				
				cout << initials << ' ' << points << '\n';
					
				player_scores.push_back(High_scores(initials, points));
			}
				
			sort(player_scores.begin(), player_scores.end(), sort_scores);
				
			if (player_scores.size() >= 5)
				set_score(5);
					
			else 
				set_score(player_scores.size());
		}
	}

	scores.close();
}

void Game_windows::write_to_file()
{	
	scores.open("Scores.txt", ios::app);
	
	if (!scores.is_open())
	{
		make_file();
		
		scores.open("Scores.txt");
		
		cout << "I made a file\n";
	}

	if (player_name.size() != 0)
	{
		scores << player_name << ' ' << to_string(score);
		
		cout << "I tried to write to the file\n";
		
		scores.close();
	}
	
	else
		scores.close();
}
void Game_windows::set_score(int num)
{	
	switch (num)
	{
		case 5:
			score_5.set_label(get_info(4));
			score_5.set_font_size(30);
			attach(score_5);
		
		case 4:
			score_4.set_label(get_info(3));
			score_4.set_font_size(30);
			attach(score_4);
			
		case 3:
			score_3.set_label(get_info(2));
			score_3.set_font_size(30);
			attach(score_3);
			
		case 2:
			score_2.set_label(get_info(1));
			score_2.set_font_size(30);
			attach(score_2);
			
		case 1:
			score_1.set_label(get_info(0));
			score_1.set_font_size(30);
			attach(score_1);
	}
}

string Game_windows::get_info(int which_one)
{
	string player, together;
	int points;
	
	player = player_scores[which_one].get_initials();
	points = player_scores[which_one].get_score();
	together = player + ' ' + to_string(points);
	
	return together;
}

void Game_windows::exit_game()		//Exits the game
{
	cout << "Exit the game\n";
	
	hide();
}

void Game_windows::enter_initials()
{
	player_name = Initials.get_string();
	
	cout << player_name << '\n';
}

void Game_windows::detach_menu()	//takes off the menu buttons
{
	detach(main_screen);
	detach(play);
	detach(instructions);
	detach(highscores);
	detach(exit);
}

void Game_windows::cb_play_game(Address, Address pw)	//Callbacks for FLTK
{
	reference_to<Game_windows>(pw).redraw();
	reference_to<Game_windows>(pw).play_game();
}

void Game_windows::cb_show_inst(Address, Address pw)
{
	reference_to<Game_windows>(pw).redraw();
	reference_to<Game_windows>(pw).show_inst();
}

void Game_windows::cb_show_high(Address, Address pw)
{
	reference_to<Game_windows>(pw).redraw();
	reference_to<Game_windows>(pw).show_high();
}

void Game_windows::cb_exit_game(Address, Address pw)
{
	reference_to<Game_windows>(pw).redraw();
	reference_to<Game_windows>(pw).exit_game();
}

void Game_windows::cb_enter_initials(Address, Address pw)
{
	reference_to<Game_windows>(pw).redraw();
	reference_to<Game_windows>(pw).enter_initials();
}

//----------------------------------------------------------------------------
	
void Game_windows::go_back()	//goes back to the main menu
{	
	cout << "numflips is " << num_flips << endl;
	
	num_flips=0;
	//attach(Initials);
	
	detach(Ok);
	detach(enter);
	detach_inst();
	detach_hard_menu();
	detach(no_high);
	detach(you_win_txt);
	detach(you_lose_txt);
	detach(lvl_diff);
	detach(username);
	detach_scores();
	detach_game();
	detach(trophy);
	detach(defeat);
	
	cout << "I'm right before detaching initials\n";
	
	detach(Initials);
	
	cout << "Go back\n";
	
	attach(main_screen);
	attach(play);
	attach(instructions);
	attach(highscores);
	attach(exit);
	main_title();
}

void Game_windows::detach_scores()
{
	detach(score_1);
	detach(score_2);
	detach(score_3);
	detach(score_4);
	detach(score_5);
	
	player_scores.erase(player_scores.begin(), player_scores.end());
}

void Game_windows::cb_go_back(Address, Address pw)		//callback for FLTK
{
	reference_to<Game_windows>(pw).redraw();
	reference_to<Game_windows>(pw).go_back();
}

//----------------------------------------------------------------------------

void Game_windows::get_inst()		//game instructions will go here
{
	inst_1.set_label("How To Play");
	inst_2.set_label("The purpose of the game is to flip an unordered stack of pancakes until they are in the ");
	inst_3.set_label("correct order while trying to use the least number of flips. When you start the game, a stack of");
	inst_4.set_label("unordered pancakes will appear before your eyes. Click the buttons next to the pancakes to ");
	inst_5.set_label("indicate the place where you want to insert the spatula. When you feel like you’re ready to flip");
	inst_6.set_label("the stack, click the ‘Flip’ button. Once you’re able to get the stack in the correct order, the game");
	inst_7.set_label("will be over and your score will be displayed. However, the game will also be over if you make ");
	inst_8.set_label("more moves than the ones that are necessary. At this point, the game will stop, and you will no ");
	inst_9.set_label("longer be able to continue."); 
	
	inst_1.set_font_size(42);
	inst_2.set_font_size(21);
	inst_3.set_font_size(21);
	inst_4.set_font_size(21);
	inst_5.set_font_size(21);
	inst_6.set_font_size(21);
	inst_7.set_font_size(21);
	inst_8.set_font_size(21);
	inst_9.set_font_size(21);
	
	attach(inst_1);
	attach(inst_2);
	attach(inst_3);
	attach(inst_4);
	attach(inst_5);
	attach(inst_6);
	attach(inst_7);
	attach(inst_8);
	attach(inst_9);
}

void Game_windows::detach_inst()	//takes off instructions when 'Ok' clicked
{
	detach(inst_1);
	detach(inst_2);
	detach(inst_3);
	detach(inst_4);
	detach(inst_5);
	detach(inst_6);
	detach(inst_7);
	detach(inst_8);
	detach(inst_9);
}

void Game_windows::attach_hard_menu()
{
	attach(lvl_2);
	attach(lvl_3);
	attach(lvl_4);
	attach(lvl_5);
	attach(lvl_6);
	attach(lvl_7);
	attach(lvl_8);
	attach(lvl_9);
}

void Game_windows::detach_hard_menu()
{
	lvl_2.hide();
	lvl_3.hide();
	lvl_4.hide();
	lvl_5.hide();
	lvl_6.hide();
	lvl_7.hide();
	lvl_8.hide();
	lvl_9.hide();
}


//----------------------------------------------------------------------------

void Game_windows::main_title()
{
	/*game_title.set_label("FlipFlaps!");
	
	game_title.set_color(maroon);
	
	game_title.set_font_size(50);
	
	attach(game_title);*/
}

void Game_windows::set_background()
{
	back_for_now.set_fill_color(Color::dark_cyan);
	back_for_now.set_color(Color::black);
	
	attach(back_for_now);
}
//----------------------------------------------------------------------------

void Game_windows::cb_hard2(Address, Address pw)
{
	reference_to<Game_windows>(pw).redraw();
	reference_to<Game_windows>(pw).set_difficulty(2);
}

void Game_windows::cb_hard3(Address, Address pw)
{
	reference_to<Game_windows>(pw).redraw();
	reference_to<Game_windows>(pw).set_difficulty(3);
}

void Game_windows::cb_hard4(Address, Address pw)
{
	reference_to<Game_windows>(pw).redraw();
	reference_to<Game_windows>(pw).set_difficulty(4);
}

void Game_windows::cb_hard5(Address, Address pw)
{
	reference_to<Game_windows>(pw).redraw();
	reference_to<Game_windows>(pw).set_difficulty(5);
}

void Game_windows::cb_hard6(Address, Address pw)
{
	reference_to<Game_windows>(pw).redraw();
	reference_to<Game_windows>(pw).set_difficulty(6);
}

void Game_windows::cb_hard7(Address, Address pw)
{
	reference_to<Game_windows>(pw).redraw();
	reference_to<Game_windows>(pw).set_difficulty(7);
}

void Game_windows::cb_hard8(Address, Address pw)
{
	reference_to<Game_windows>(pw).redraw();
	reference_to<Game_windows>(pw).set_difficulty(8);
}

void Game_windows::cb_hard9(Address, Address pw)
{
	reference_to<Game_windows>(pw).redraw();
	reference_to<Game_windows>(pw).set_difficulty(9);
}


//----------------------------------------------------------------------------


void Game_windows::set_difficulty(int diff)
{
	detach_hard_menu();
	detach(username);
	detach(lvl_diff);
	detach(Initials);
	detach(enter);
	
	int num_pancakes = diff;
	
	cout << "Lvl " << diff << '\n';
	
	run_game(diff);
}
	

//----------------------------------------------------------------------------

int Game_windows::run_game(int p_cakes)
{
	int pwidth, pheight, table, hscaler, wscaler, pancakeY;
	int flip_Y, flip_X, flip_width, flip_height;
	
	wscaler = 50;	//pancake width
	table = 250;	//bottom margin. Pancakes rest on this
	pheight = 50;	//height for all pancakes
	flip_X = 160;
	flip_width = 80;
	flip_height = 50;	//same as pancake height 

	//detach(game_title);

		cout << "I'm at the beginning of flip\n";
	bool lose = false;
		
	handle_pancakes(p_cakes, pwidth, wscaler, pancakeY, table, pheight);

	generate_flip_buttons(p_cakes, pancakeY, table, pheight, flip_Y, flip_X,
						flip_width,flip_height);

	score = calculate_score(0);
	your_score.set_label("Score: "+ to_string(score));
	your_score.set_font_size(20);
	attach(your_score);

	attach(flips_to_win);
	tableleg.set_fill_color(dark_brown);
	tableleg2.set_fill_color(dark_brown);
	tabletop.set_fill_color(dark_brown);
	attach(tableleg);
	attach(tableleg2);
	attach(tabletop);

	

	cout <<"Game's running\n";
}

void Game_windows::flip() //happens when a button is clicked
{
	cout << "I'm at the beginning of flip\n";
	bool lose = false;
	
	++num_flips;
	score = calculate_score(num_flips);
	your_score.set_label("Score: "+ to_string(score));

	if(score != 0 && !lose)
	{	
		int flip_id, pheight, pancakeY, flip_Y, h, table;
		
		pheight = 50;
		table = 250;
		pancakeY = (y_max() - table) - pheight * flip_info.size();
		h = 50;		//pancakes height
		flip_Y = pheight + pancakeY - pheight / 2;
		

		if (Fl::event_y() > flip_Y)	//if a flip button below the first button's Y is clicked
		{
			int flip_id = 1 + ((Fl::event_y() - flip_Y) / h); //calculates which button clicked
			
			cout << "clicked button no. " << flip_id << endl;
			
			do_flip(flip_id);
		}
	}

	else if (score == 0 || score < 0) {
		you_lose();
		lose = true;
	}

	if (!lose)
	{
		for (int i = 0; i < widths.size() - 1; ++i) //check if game has been won
		{
			if (pancakes[i]->width() > pancakes[i + 1]->width())
				++num_arranged;
		}
		
		if (num_arranged == widths.size() - 1)
			you_win();

		else
			num_arranged = 0;
		
		cout << "I'm at the end of flip\n";
	}
}

void Game_windows::cb_flip(Address, Address pw)
{	
	reference_to<Game_windows>(pw).redraw();
	reference_to<Game_windows>(pw).flip();
}

//----------------------------------------------------------------------------

int Game_windows::calculate_score(int flips)
{	

	int score, min_flips;

	
	reverse(widths.begin(), widths.end());
	
	solution = find_solution(widths);
	
	reverse(widths.begin(), widths.end());
	
	min_flips = solution->size();
	
	cout<<"solution size is "<<solution->size()<<endl;
	
	flips_to_win.set_label("You've used " + to_string(flips) + " flip(s)");
	flips_to_win.set_font_size(20);
	
	return score = (100 - 10 * (flips - min_flips)) * 6;
}

void Game_windows::you_win()
{
	score = calculate_score(num_flips);
	you_win_txt.set_label("You Win! Score: "+to_string(score));
	you_win_txt.set_font_size(50);
	
	attach(you_win_txt);
	attach(replay);
	attach(menu_button);
	attach(trophy);
	detach(tabletop);
	detach(tableleg);
	detach(tableleg2);

	cout << "The game has ended. Either the user made\n" 
		<< "too many moves or arranged the pancakes in order\n"
		<< "The score was " << calculate_score(num_flips) << '\n';
	cout << "Player_size: " << player_name.size() << '\n';
		
	write_to_file();
		
	num_flips = 0;
	num_arranged = 0;

	detach_game();
}

void Game_windows::you_lose()
{
	you_lose_txt.set_label("You Lose!");
	score = calculate_score(num_flips);
	you_lose_txt.set_font_size(50);
	
	attach(you_lose_txt);
	attach(replay);
	attach(menu_button);
	attach(defeat);
	detach(tabletop);
	detach(tableleg);
	detach(tableleg2);
	
	cout << "The game has ended. Either the user made\n" 
		<< "too many moves or arranged the pancakes in order\n"
		<< "The score was " << calculate_score(num_flips) << '\n';
	cout << "Player_size: " << player_name.size() << '\n';
		
	write_to_file();
		
	
	num_flips = 0;
	num_arranged = 0;

	detach_game();
}

void Game_windows::detach_game()
{		
		for (int i = 0; i < pancakes.size(); ++i)
		{
			Rectangle* pancake = (pancakes[i]);
			Rectangle& pancake_ref = (*pancake);
			
			Button* flip_button = (flip_info[i].button_ptr);
			Button& flip_ref = (*flip_button);

			Line* line = lines[i];
			Line& line_ref = (*line);
			
			detach(line_ref);
			detach(pancake_ref);
			detach(flip_ref);
			detach(your_score);
			detach(flips_to_win);
		}
	
	pancakes.erase(pancakes.begin(), pancakes.end());
	flip_info.erase(flip_info.begin(), flip_info.end());
	lines.erase(lines.begin(),lines.end());
	widths.erase(widths.begin(), widths.end());
	
	cout << "Size of pancake vector = " << pancakes.size() << '\n';
	cout << "Size of button vector = " << flip_info.size() << '\n';

	detach(Ok);
}

//----------------------------------------------------------------------------

void Game_windows::do_flip(int flip_id)
{
	cout << "I'm at the beginning of do_flip\n";
	
	int num_to_flip = flip_id;
	int midpoint = num_to_flip / 2;

	int p_cakes = flip_info.size();//how many pancakes there are 

	odd_flip(num_to_flip, p_cakes, midpoint);
	even_flip(num_to_flip, p_cakes, midpoint);
	
	cout << "I'm at the end of do flip\n";
}


void Game_windows::handle_pancakes(int p_cakes, int pwidth, int wscaler, 
									int pancakeY, int table, int pheight)
{
	random_device rd; //used for shuffling our vector
	mt19937 generator(rd());	//random generator parameter
	
	for (int i = 1; i <= p_cakes; ++i)	//our widths, which will be scaled by wscaler
	{
		widths.push_back(i);
		
		cout << "Rectangle widths: " << widths[i - 1] << '\n';
	}
	
	shuffle(widths.begin(), widths.end(), generator); //shuffles our vector
	
	for (int i = 1; i <= p_cakes; ++i)
	{	
		pwidth = widths[i-1] * wscaler;
		
		cout << "pwidth: " << pwidth << '\n';
		
		pancakeY = (y_max() - table) - pheight * i;
		
		Rectangle* pancake = new Rectangle(Point(x_max() / 2 - pwidth / 2, pancakeY), pwidth, pheight);
		pancake->set_fill_color(light_brown);
		pancake->set_color(brown_trim);
		Rectangle& pancake_ref = (*pancake);

		pancakes.push_back(pancake);
		
		attach(pancake_ref);
	}
	cout << "Pancakes were generated.\n";
}

void Game_windows::generate_flip_buttons(int p_cakes, int pancakeY, int table, int pheight, int flip_Y, 
									int flip_X, int flip_width, int flip_height)
{
	for (int i = 0; i < p_cakes; ++i)
	{
		pancakeY = (y_max() - table) - pheight * i;	
		flip_Y = pancakeY - pheight / 2;
		
		Button* flip_button = new Button (Point(flip_X, flip_Y), flip_width, flip_height, "FLIP", cb_flip);
		Button& flip_ref = (*flip_button);

		flip_info.push_back({i + 1, flip_button});	//stores buttons
		
		int line_width = 300/p_cakes;
		Line* line= new Line(Point(	flip_X+flip_width,
									flip_Y+flip_height/2),
					 		Point(	flip_X+flip_width+line_width,
					 				flip_Y+flip_height/2));
		line->set_style(Line_style(Line_style::dash, 3));
		Line& line_ref = (*line);
		lines.push_back(line);

		attach(line_ref);
		attach(flip_ref);
	}

	cout << "Buttons were generated\n";
}

void Game_windows::cb_replay(Address, Address pw)		//callback for FLTK
{
	reference_to<Game_windows>(pw).redraw();
	reference_to<Game_windows>(pw).do_replay();
}

void Game_windows::cb_game_go_back(Address, Address pw)		//callback for FLTK
{
	reference_to<Game_windows>(pw).redraw();
	reference_to<Game_windows>(pw).game_go_back();
}

void Game_windows::game_go_back()
{
	score=0;
	detach(menu_button);
	detach(replay);
	go_back();
	
}

void Game_windows::do_replay()
{	
	detach(replay);
	detach(menu_button);
	go_back();
	play_game();
}

void Game_windows::odd_flip(int num_to_flip, int p_cakes, int midpoint)
{
	if (num_to_flip % 2 == 1)						//odd num flip
	{	
		for (int i = 0; i < midpoint + 1; ++i)
		{
			int yposa = pancakes[p_cakes - midpoint + i - 1]->yPos();
			int yposb = pancakes[p_cakes - midpoint - i - 1]->yPos();
			int move = yposb - yposa;

			pancakes[p_cakes - midpoint + i - 1]->move(0, move);
			pancakes[p_cakes - midpoint - i - 1]->move(0, -move);

			int swapY = yposa; //assign new swapped y values
			pancakes[p_cakes - midpoint + i - 1]->set_yPos(yposb);
			pancakes[p_cakes - midpoint - i - 1]->set_yPos(swapY);

			swap(pancakes[p_cakes - midpoint + i - 1],	//swap rects in array
				pancakes[p_cakes - midpoint - i - 1]);
		}
		Fl::redraw();
	}
}

void Game_windows::even_flip(int num_to_flip, int p_cakes, int midpoint)
{
	if (num_to_flip % 2 == 0)						//even number flip
	{ 											
		for (int i = 0; i < midpoint; ++i)
		{	
			int yposa = pancakes[p_cakes - midpoint + i]->yPos();//get y's
			int yposb = pancakes[p_cakes - midpoint - i - 1]->yPos();
			int move = yposb - yposa;

			//moves the pancakes to the other's position
			pancakes[p_cakes - midpoint + i]->move(0, move);
			pancakes[p_cakes - midpoint - i - 1]->move(0, -move);


			//assigns new swapped y values since move doesn't record
			// them :(
			int swapY = yposa; 
			pancakes[p_cakes-midpoint + i]->set_yPos(yposb);
			pancakes[p_cakes-midpoint - i - 1]->set_yPos(swapY);

			//swaps addresses of each pancake so that they occupy
			//the other's array index, used to reflect the new
			//structure of pancakes in the array itself, ie
			//if bot pancake is now top, its index goes [0] to [last]
			//so next time we can find it when the loop does its logic
			swap(pancakes[p_cakes - midpoint + i],
				pancakes[p_cakes - midpoint - i - 1]);
		}
		Fl::redraw();//save cycles? by redrawing only once
	}
}