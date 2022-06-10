#include <vector>
#include <string>

#include "othello.hpp"
#include "heuristic.hpp"

int directions[16] =
{  1,  0 //droite
, -1,  0 //gauche
,  0,  1 //bas
,  0, -1 //haut
,  1,  1 //droite-bas
,  1, -1 //droite-haut
, -1,  1 //gauche-bas
, -1, -1 //gauche-haut
};

bool possibleMove(int** board, const int& x, const int& y, const int& player)
{
	if(board[x][y] != 0) return false;
	for(int dir_it = 0; dir_it < int(sizeof(directions) / sizeof(int)); dir_it+=2)
	{
		bool oponent_found(false);
		for(int x_it = x + directions[dir_it], y_it = y + directions[dir_it + 1]; x_it > -1 && y_it > -1 && x_it < BOARD_SIZE && y_it < BOARD_SIZE; x_it += directions[dir_it], y_it += directions[dir_it + 1])
		{
			if(board[x_it][y_it] == 0 || (board[x_it][y_it] == player && oponent_found == false)) break;
			else if(board[x_it][y_it] == player * -1) oponent_found = true;
			else return true;
		}
	}

	return false;
}

const std::vector<int> PossibleMoves(int** board, const int& player)
{
	std::vector<int> moves;

	for(int y_it = 0; y_it < BOARD_SIZE; ++y_it)
	{
		for(int x_it = 0; x_it < BOARD_SIZE; ++x_it)
		{
			if(possibleMove(board, x_it, y_it, player))
			{
				moves.push_back(x_it);
				moves.push_back(y_it);
			}
		}
	}
	return moves;
}

const std::vector<int> PossibleMovesOptimized(int** board, const int& player)
{
	std::vector<int> moves;

	for(int y = 0; y < BOARD_SIZE; ++y)
	{
		for(int x = 0; x < BOARD_SIZE; ++x)
		{
			if(possibleMove(board, x, y, player))
			{
				moves.push_back(x);
				moves.push_back(y);
			}
		}
	}
	return moves;
}

void Update(int** board, const int& x, const int& y, const int& player)
{
	board[x][y] = player;

	for(int dir_it = 0; dir_it < int(sizeof(directions) / sizeof(int)); dir_it+=2)
	{
		bool propagate(false);
		bool oponent_found(false);
		for(int x_it = x + directions[dir_it], y_it = y + directions[dir_it + 1]; x_it > -1 && y_it > -1 && x_it < BOARD_SIZE && y_it < BOARD_SIZE; x_it += directions[dir_it], y_it += directions[dir_it + 1])
		{
			if(board[x_it][y_it] == 0 || (board[x_it][y_it] == player && oponent_found == false)) break;
			else if(board[x_it][y_it] == player * -1) oponent_found = true;
			else propagate = true;
		}
		if(propagate)
		{
			for(int x_it = x + directions[dir_it], y_it = y + directions[dir_it + 1]; x_it > -1 && y_it > -1 && x_it < BOARD_SIZE && y_it < BOARD_SIZE; x_it += directions[dir_it], y_it += directions[dir_it + 1])	
			{
				if(board[x_it][y_it] == player * -1)	board[x_it][y_it] = player;
				else break;
			}
		}
	}
}