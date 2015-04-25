/*
Ruben Cardenas, Stephen Brownlee, Pedro Alvares
High_scores.h
To be used with FlipFlaps
*/

#include "std_lib_facilities_4.h"

struct High_scores
{
	High_scores(string init, int scre);
	
	int get_score();
	void set_score(int score);
	string get_initials();
	
	private:
		string initials;
		int score;
};