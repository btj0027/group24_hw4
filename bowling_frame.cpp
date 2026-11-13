#include "bowling_frame.h"
#include <random>

std::random_device dev;
std::mt19937 rng(dev());

Bowling_Frame::Bowling_Frame(int fnum)
{
	score1_ = 0;
	score2_ = 0;
	score3_ = 0;
	strike_ = false;
	spare_ = false;
	frame_num_ = fnum;
	frame_score_ = 0;
	roll_one_ = false;
	roll_two_ = false;
	roll_three_ = false;

	next_frame_ = NULL;
	prev_frame_ = NULL;

}

Bowling_Frame::~Bowling_Frame()
{
	free(next_frame_);
	free(prev_frame_);
}

Bowling_Frame* Bowling_Frame::next_frame() { return next_frame_; }
void Bowling_Frame::next_frame( Bowling_Frame * new_frame ) { next_frame_ = new_frame; }

Bowling_Frame* Bowling_Frame::prev_frame() { return prev_frame_; }
void Bowling_Frame::prev_frame( Bowling_Frame * new_frame ) { prev_frame_ = new_frame; }

int Bowling_Frame::score1()				{ return score1_; }
void Bowling_Frame::score1( int score )	{ score1_ = score; }

int Bowling_Frame::score2()				{ return score2_; }
void Bowling_Frame::score2( int score )	{ score2_ = score; }

int Bowling_Frame::score3()				{ return score3_; }
void Bowling_Frame::score3( int score )	{ score3_ = score; }

bool Bowling_Frame::strike() 			{ return strike_; }
void Bowling_Frame::strike(bool value )	{ strike_ = value; }

bool Bowling_Frame::spare() 			{ return spare_; }
void Bowling_Frame::spare(bool value )	{ spare_ = value; }

int Bowling_Frame::frame_num()
{
	return frame_num_;
}

int Bowling_Frame::frame_score()
{
	return frame_score_; 
}

void Bowling_Frame::update_scores()
{
	std::uniform_int_distribution<std::mt19937::result_type> dist10(0, 10);
	// Tenth frame logic
	if (frame_num_ == 10) {

		// Handle tenth frame logic for strikes
    	if (strike_) {

        	// Generate second roll
        	if (!roll_two_) {
            	std::uniform_int_distribution<std::mt19937::result_type> dist(0, 10);
            	score2_ = dist(rng);
            	roll_two_ = true;
        	}
        

        	// Generate third roll
        	if (!roll_three_) {

            	std::uniform_int_distribution<std::mt19937::result_type> dist(0, 10);
            	score3_ = dist(rng);
            	roll_three_ = true;
        	}
    	}
    	else if (spare_) {

        	// Generate third roll
        	if (!roll_three_) {

        	    std::uniform_int_distribution<std::mt19937::result_type> dist(0, 10);
        	    score3_ = dist(rng);
        	    roll_three_ = true;
        	}
    	}

    	// Calculate tenth frame score
    	frame_score_ = score1_ + score2_ + score3_;
	}
	else {
		// Handle frames 1-9
		if (!roll_one_)
		{
			score1_ = dist10(rng);
			roll_one_ = true;

			if(score1_ == 10) strike_ = true; 
		}
		else if ( !strike_ && !roll_two_ ) 	
		{
			std::uniform_int_distribution<std::mt19937::result_type> distX(0,10 - score1_);
			score2_ = distX(rng); 
			roll_two_ = true;

			if ((score1_ + score2_) == 10) spare_ = true;
		}
	}
	// Update the next frame's scores before calculating bonuses
	if (next_frame_) {
		 	next_frame_->update_scores();
		}
	// Add score before considering strikes and spares bonuses
	frame_score_ += score1_ + score2_;

	// Add Spare bonus
	if (spare_ && next_frame_)
	{
		frame_score_ += next_frame_->score1();
	}
	// Add Strike bonus
	if (strike_ && next_frame_)
	{
		frame_score_ += next_frame_->score1();
		if (next_frame_->strike() && next_frame_->next_frame_){
			frame_score_ += next_frame_->next_frame()->score1();
		}
		else {
			frame_score_ += next_frame_->score2();
		}
	}
}


