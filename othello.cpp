#include <iostream>
#include <string>
#include <vector>
#include <tuple>
#include <thread>
#include <chrono>

#include "color.hpp"
#include "play.hpp"
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

bool Othello::possibleMove(const int& x, const int& y, const int& player) const
{
	int directions[] =
	{  1,  0 //droite
	, -1,  0 //gauche
	,  0,  1 //bas
	,  0, -1 //haut
	,  1,  1 //droite-bas
	,  1, -1 //droite-haut
	, -1,  1 //gauche-bas
	, -1, -1 //gauche-haut
	};

	for(int dir_it = 0; dir_it < int(sizeof(directions) / sizeof(int)); dir_it+=2)
	{
		bool oponent_found(false);
		for(int x_it = x + directions[dir_it], y_it = y + directions[dir_it + 1]; x_it > -1 && y_it > -1 && x_it < BOARD_SIZE && y_it < BOARD_SIZE; x_it += directions[dir_it], y_it += directions[dir_it + 1])
		{
			if(board_[x_it][y_it] == 0 || (board_[x_it][y_it] == player && oponent_found == false)) break;
			else if(board_[x_it][y_it] == player * -1) oponent_found = true;
			else return true;
		}
	}

	return false;
}

const std::vector<int> Othello::PossibleMoves(const int& player) const
{
	std::vector<int> moves;

	for(int y_it = 0; y_it < BOARD_SIZE; ++y_it)
	{
		for(int x_it = 0; x_it < BOARD_SIZE; ++x_it)
		{
			if(possibleMove(x_it, y_it, player))
			{
				moves.push_back(x_it);
				moves.push_back(y_it);
			}
		}
	}
	return moves;
}

void Othello::Update(const int& x, const int& y, const int& player)
{
	board_[x][y] = player;
}

template<class C>
void Othello::Play(const std::vector<int>& moves, const int& player)
{
	bool valid_coords(false);
	std::tuple<int, int> coords;
	
	system("clear && reset");
	while(!valid_coords)
	{
		std::cout << *this << std::endl;	
		std::cout << "[player " << (-player + 1)/2 + 1 << " turn] possible moves:" << std::endl;
		for(int i = 0; i < int(moves.size()); i+=2)
			std::cout << "[" << char(int('a') + moves[i]) << moves[i+1]+1 << "] ";
		std::cout << std::endl;

		coords = C::Play(moves, player, board_);
		for(int i = 0; i < int(moves.size()); i+=2)
		{
			if(std::get<0>(coords) == moves[i] && std::get<1>(coords) == moves[i+1])
				valid_coords = true;
		}
		if(!valid_coords)
			std::cerr << std::endl << error_col.start() << "coords [" << char(int('a') + std::get<0>(coords)) << std::get<1>(coords) + 1 << "] are not valid, please choose something else" << error_col.end() << std::endl;
		std::this_thread::sleep_for(std::chrono::seconds(idle_time_));	
	}
	Update(std::get<0>(coords), std::get<1>(coords), player);
}
template void Othello::Play<Human>(const std::vector<int>& moves, const int& player);
template void Othello::Play<IA>(const std::vector<int>& moves, const int& player);

bool Othello::Loop()
{
	bool end(false), passed(false);
	int player(1);
	std::string player_type(player_one_);
	while(!end)
	{	
		const std::vector<int> moves = PossibleMoves(player);
		
		if(!moves.empty())
		{
			passed = false;

			if(player_type == "human")		Play<Human>(moves, player);
			else					Play<IA>(moves, player);
		}
		else
		{
			if(passed) end = true;
			passed = true;
		}
		
		player = -player;
		player_type = (player == 1) ? player_one_: player_two_;
	}
	std::cout << board_col_.start() << "player " << (-player + 1)/2 + 1 << " wins !" << board_col_.end() << std::endl;
	return true;
}
