#include <iostream>
#include <vector>
#include <string>
#include <tuple>

#include "color.hpp"
#include "play.hpp"
#include "othello.hpp"

std::tuple<int, int> Human::Play(const std::vector<int>& moves, const int& player, int** board)
{
	std::cout << "Play at: " << std::endl;
	std::string input;
	std::cin >> input;

	system("clear && reset");	

	if(input.size() != 2)
	{
		std::cerr << error_col.start() << "[" << input << "] is not a valid coordinate" << error_col.end() << std::endl;
		return std::tuple<int, int>(-1, -1);	
	}
	if(input[0] < 'a' || input[0] >= char(int('a') + BOARD_SIZE) || input[1] < '1' || input[1] >= char(int('1') + BOARD_SIZE))
	{
		std::cerr << error_col.start() << "[" << input << "] is not in the board" << error_col.end() << std::endl;
		return std::tuple<int, int>(-1, -1);
	}
	
	return std::tuple<int, int>(int(input[0] - 'a'), int(input[1] - '1'));
}

std::tuple<int, int> IA::Play(const std::vector<int>& moves, const int& player, int** board)
{
	return std::tuple<int, int>(0, 0);
}

