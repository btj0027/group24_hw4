#include <iostream>
#include <cstdlib>
#include "bowling_frame.h"

using namespace std;

const int NUM_FRAMES = 10;
const int MAX_ROLLS = 21;

int current_game_total(Bowling_Frame * first_frame)
{
	Bowling_Frame * temp = first_frame;
	int game_total = 0;
	while(temp)
	{
		game_total += temp->frame_score();
		temp = temp->next_frame();
	}
	return game_total;	
}

int main(int argc, char * argv[])
{
	// number of players
	if (argc < 2) {
		cout << "Usage: " << argv[0] << " <num_players>" << endl;
		return 0;
	}

	int num_players = atoi(argv[1]);
	if (num_players < 1) {
		cout << "Error: number of players must be a positive integer." << endl;
		return 0;
	}

	cout << "Player count is: " << num_players << endl;

	// array of Bowling_Frame pointers
	Bowling_Frame ** players = new Bowling_Frame*[num_players];

	for (int p = 0; p < num_players; p++) {
		players[p] = new Bowling_Frame(1);
		Bowling_Frame * prev = players[p];

		for (int f = 2; f <= NUM_FRAMES; f++) {
			Bowling_Frame * frame = new Bowling_Frame(f);
			prev->next_frame(frame);
			frame->prev_frame(prev);
			prev = frame;
		}
	}

	for (int p = 0; p < num_players; p++) {
		for (int roll = 0; roll < MAX_ROLLS; roll++) {
			players[p]->update_scores();
		}
	}

	for (int p = 0; p < num_players; p++) {
		Bowling_Frame * traverse = players[p];
		while (traverse) {
			cout << "Frame " << traverse->frame_num() << ":" << endl
					<< " Score 1: " << traverse->score1() << endl
					<< " Score 2: " << traverse->score2() << endl;
			if (traverse->frame_num() == NUM_FRAMES && (traverse->strike() || traverse->spare()))
				cout << " Score 3: " << traverse->score3() << endl;
			traverse = traverse->next_frame();
		}
		cout << endl << "Total Game Score for player " << (p+1) << ": "
				<< current_game_total(players[p]) << endl << endl;
	}

	for (int p = 0; p < num_players; p++) {
		Bowling_Frame * current = players[p];
		while (current) {
			Bowling_Frame * next = current->next_frame();
			delete current;
			current = next;
		}
	}

	delete[] players;

	return 0;
}
