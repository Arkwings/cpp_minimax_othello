#include <iostream>
#include <vector>
#include <string>
#include <tuple>

#include "color.hpp"
#include "named_pipe.hpp"
#include "play.hpp"
#include "othello.hpp"

Pipe* IA::IA_com_ = new Pipe("IA_named_pipe", 0777);

std::tuple<int, int> Human::Play()
{
	std::cout << "Play at: " << std::endl;
	std::string input;
	std::cin >> input;

	//system("clear");	

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

std::tuple<int, int> IA::Play(const int& player, int** board, const int& idle_time)
{
	std::string text;

	text.push_back(char(int('0') + player));
	text.push_back(char(int('0') + idle_time));
	for(int it1 = 0; it1 < BOARD_SIZE; ++it1)
	{
		for(int it2 = 0; it2 < BOARD_SIZE; ++it2)
			text.push_back(char(int('0') + board[it2][it1]));
	}

	IA_com_->Write(text);
	IA_com_->Read(text);
	std::cout << "IA play : " << text << std::endl;

	return std::tuple<int, int>(int(text[0] - 'a'), int(text[1] - '1'));
}

