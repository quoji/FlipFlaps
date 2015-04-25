/*
Ruben Cardenas, Stephen Brownlee, Pedro Alvares
High_scores.h
To be used with FlipFlaps
*/

#include "std_lib_facilities_4.h"
#include "High_scores.h"

High_scores::High_scores(string init, int scre) :
	initials(init),
	score(scre)
	{
	
	}

int High_scores::get_score()
{
	return score;
}

void High_scores::set_score(int scre)
{
	score = scre;
}

string High_scores::get_initials()
{
	return initials;
}