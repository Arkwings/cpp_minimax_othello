#include <string>
#include <iostream>
#include <vector>

#include "othello.hpp"
#include "heuristic.hpp"
#include "named_pipe.hpp"

int main()
{
	Pipe IA_pipe("IA_named_pipe", 0777);
	int** board = new int*[BOARD_SIZE];
	for(int i = 0; i < BOARD_SIZE; ++i) board[i] = new int[BOARD_SIZE];
	std::string text, heuri;
	int player(0), time(0);

	while(1)
	{
		//get data
		IA_pipe.Read(text);
		//std::cout << text << std::endl;
		
		player = int(text[0] - '0');
		time = int(text[1] - '0');
		//std::cout << player << std::endl;
		for(int y = 0; y < BOARD_SIZE; ++y)
		{
			for(int x = 0; x < BOARD_SIZE; ++x)
			{
				board[x][y] = int(text[y * BOARD_SIZE + x + 2] -'0');	
				//std::cout << board[x][y];
			}
		}
		//std::cout << std::endl << std::endl;

		//send heuri
		IA_pipe.Write(heuristics(board, player));
	}

	for(int i = 0; i < BOARD_SIZE; ++i) delete board[i];
	delete board;

	return 0;
}
