#pragma once

#define BOARD_SIZE 8

class Othello
{
public:
        Othello(const std::string& player_one, const std::string& player_two, const int& idle_time)
        : player_one_(player_one)
        , player_two_(player_two)
        , idle_time_(idle_time)
	, board_(new int*[BOARD_SIZE])
        {
		for(int it = 0; it < BOARD_SIZE; ++it)
			board_[it] = new int[BOARD_SIZE];
		board_[BOARD_SIZE/2][BOARD_SIZE/2] = -1;
		board_[BOARD_SIZE/2-1][BOARD_SIZE/2-1] = -1;
		board_[BOARD_SIZE/2-1][BOARD_SIZE/2] = 1;
		board_[BOARD_SIZE/2][BOARD_SIZE/2-1] = 1;	
	}

        ~Othello()
        {
		for(int it = 0; it < BOARD_SIZE; ++it)
			delete board_[it];
		delete board_;
	}

	friend std::ostream& operator<<(std::ostream& os, const Othello& game);
	const std::vector<int> PossibleMoves(const int& player) const;
	void Play(const std::vector<int>& moves, const int& player);
	void Update(const int& x, const int& y, const int& player);
	bool Loop();

	static const Color board_col_;
	static const Color side_col_;
	static const Color p1_col_;
	static const Color p2_col_;
private:
	friend void printLine(std::ostream& os, const Othello& game, const int& line);
	bool possibleMove(const int& x, const int& y, const int& player) const;
	void winner() const;

        const std::string player_one_;
        const std::string player_two_;
        const int idle_time_;

	int** board_;
};
