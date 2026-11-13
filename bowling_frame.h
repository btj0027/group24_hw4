#ifndef BOWLING_FRAME_H
#define BOWLING_FRAME_H


class Bowling_Frame
{
	private:
		int score1_;
		int score2_;
		bool strike_;
		bool spare_;
		bool roll_one_;
		bool roll_two_;

		int total_score_;
		int frame_num_;
		int frame_score_;

		Bowling_Frame * next_frame_;
		Bowling_Frame * prev_frame_;


	public:
		Bowling_Frame(int fnum);
		~Bowling_Frame();

		Bowling_Frame* next_frame(); 	
		void next_frame(Bowling_Frame * new_frame);

		Bowling_Frame* prev_frame(); 	
		void prev_frame(Bowling_Frame * new_frame);

		int score1();
		void score1(int score);
		int score2();
		void score2(int score);
		bool strike();
		void strike(bool value);
		bool spare();
		void spare(bool value);
		int frame_num();
		int frame_score();
		void update_scores();
};

#endif
