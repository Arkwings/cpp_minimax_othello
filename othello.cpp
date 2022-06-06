#include <iostream>
#include <string>
#include <vector>

#include "color.hpp"
#include "othello.hpp"

const Color Othello::board_col_("22","34");
const Color Othello::side_col_("231","22");
const Color Othello::p1_col_("231", "232");
const Color Othello::p2_col_("232", "231");

void printXCoords(std::ostream& os)
{
	os << "  " << Othello::side_col_.start();
	for(char it = 'a'; it < 'i'; ++it)
		os << " " << it;
	os << Othello::side_col_.end() << std::endl;
}

void printYCoords(std::ostream& os, const int& line)
{
	os << Othello::side_col_.start() << " " << line + 1 << Othello::side_col_.end();
}

void printLine(std::ostream& os, const Othello& game, const int& line)
{
	for(int it = 0; it < BOARD_SIZE; ++it)
	{
		if(game.board_[it][line] == 1)
			os << Othello::p1_col_.start() << "[]" << Othello::p1_col_.end();
		else if(game.board_[it][line] == -1)
			os << Othello::p2_col_.start() << "[]" << Othello::p2_col_.end();
		else
			os << Othello::board_col_.start() << "[]" << Othello::board_col_.end();
	}
}

std::ostream& operator<<(std::ostream& os, const Othello& game)
{
	os << std::endl;
	printXCoords(os);
	for(int it = 0; it < BOARD_SIZE; ++it)
	{
		printYCoords(os, it);
		printLine(os, game, it);
		printYCoords(os, it);
		os << std::endl;
	}
	printXCoords(os);
	
	return os;
}

std::vector<int> Othello::PossibleMoves() const
{
	return std::vector<int>();
}

bool Othello::Update(const int& x, const int& y)
{

	return true;
}

bool Othello::Loop()
{
	std::cout << *this << std::endl;
	return true;
}
