#include <iostream>
#include <string>
#include <vector>

#include "color.hpp"
#include "othello.hpp"

const Color Othello::board_col_("232","34");
const Color Othello::side_col_("231","22");

void printXCoords(std::ostream& os)
{
	os << "  " << Othello::side_col_.start() << " ";
	for(char it = 'a'; it < 'i'; ++it)
		os << it << " ";
	os << Othello::side_col_.end() << std::endl;
}

void printYCoords(std::ostream& os, const int& line)
{
	os << Othello::side_col_.start() << " " << line + 1 << Othello::side_col_.end();
}

void printLine(std::ostream& os, const Othello& game, const int& line)
{
	os << Othello::board_col_.start() << " ";
	for(int it = 0; it < BOARD_SIZE; ++it)
		os << game.board_[it][line] << " ";
	os << Othello::board_col_.end();
}

std::ostream& operator<<(std::ostream& os, const Othello& game)
{
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
