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
	}

        ~Othello()
        {
		for(int it = 0; it < BOARD_SIZE; ++it)
			delete board_[it];
		delete board_;
	}

	friend std::ostream& operator<<(std::ostream& os, const Othello& game);
	std::vector<int> PossibleMoves() const;
	bool Update(const int& x, const int& y);
	bool Loop();

	static const Color board_col_;
	static const Color side_col_;
private:
	friend void printLine(std::ostream& os, const Othello& game, const int& line);

        const std::string player_one_;
        const std::string player_two_;
        const int idle_time_;

	int** board_;
};
