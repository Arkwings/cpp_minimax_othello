#pragma once

class Othello
{
public:
        Othello(const std::string& player_one, const std::string& player_two, const int& idle_time)
        : player_one_(player_one)
        , player_two_(player_two)
        , idle_time_(idle_time)
        {}

        ~Othello()
        {}

	friend std::ostream& operator<<(std::ostream& os, const Othello& game);
	std::vector<int> PossibleMoves();
	bool Update(const int& x, const int& y);

private:
        const std::string player_one_;
        const std::string player_two_;
        const int idle_time_;
};
