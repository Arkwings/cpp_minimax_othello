#include <cstdlib>
#include <ctime>

#include <string>
#include <vector>
#include <iostream>
#include <random>

#include "othello.hpp"
#include "heuristic.hpp"
#include "montecarlo.hpp"

std::mt19937 rng(time(NULL));

void copyArray(int ** board_src, int** board_dst)
{
    for(int y = 0; y < BOARD_SIZE; ++y)
    {
        for(int x = 0; x < BOARD_SIZE; ++x)
        {
            board_dst[x][y] = board_src[x][y];
        }
    }
}

bool playRandomGame(int ** board, const int& color)
{
	bool end(false), passed(false);
    int move(-1), color_copy(color), points(0);
    
	while(!end)
	{	
		const std::vector<int> moves = PossibleMoves(board, color_copy);
        std::uniform_int_distribution<int> gen(0, moves.size()/2 - 1); // uniform, unbiased
		
		if(!moves.empty())
		{
			passed = false;
			move = gen(rng);
            Update(board, moves[move*2], moves[move*2+1], color_copy);    //update the board
		}
		else
		{
			if(passed) end = true;
			passed = true;
		}
		
		color_copy = -color_copy;
	}

	for(int it1 = 0; it1 < BOARD_SIZE; ++it1)
	{
		for(int it2 = 0; it2 < BOARD_SIZE; ++it2)
		{
			points += board[it2][it1];
		}
	}

    if((color == 1 && points > 0) || (color == -1 && points < 0))    return true;
    return false;
}

const std::string montecarlo(int** board, const int& color, const int& IA_time)
{
    int** new_board = new int*[BOARD_SIZE];
	for(int i = 0; i < BOARD_SIZE; ++i) new_board[i] = new int[BOARD_SIZE];

    std::vector<int> possibleMoves(PossibleMoves(board, color));
    std::vector<int> accMoves(possibleMoves.size()/2);
    std::vector<int> winMoves(possibleMoves.size()/2);
    for(int i = 0; i < int(accMoves.size()); ++i)    accMoves[i] = 0;
    for(int i = 0; i < int(winMoves.size()); ++i)    winMoves[i] = 0;
    std::uniform_int_distribution<int> gen(0, possibleMoves.size()/2 - 1); // uniform, unbiased

    int iterations(0);
    int move(-1);
    std::string coord("");

    time_t start_time(time(NULL));
    time_t moving_time(start_time);
    time_t end_time(start_time + time_t(IA_time));
    time_t iteration_time(end_time);

    std::cout << "montecarlo start time: " << ctime(&start_time) << std::endl;

    do
    {
        copyArray(board, new_board);                                                //reste array
        move = gen(rng);                                                            //pick move
        Update(new_board, possibleMoves[move*2], possibleMoves[move*2+1], color);   //update the board
        ++accMoves[move];                                                           //update this move counter
        if(!playRandomGame(board, -color))    ++winMoves[move];                     //do a random game and update win counter

        moving_time = time(NULL);
        if(++iterations == 1)   iteration_time = moving_time - start_time;
    } while (moving_time < end_time - 3 * iteration_time); //we remove 3 iteration times to have the time to quit the program

    std::cout << "montecarlo end time: " << ctime(&end_time) << std::endl;

    for(int i = 0; i < BOARD_SIZE; ++i) delete new_board[i];
    delete new_board;

    float best(-1);
    int best_index(-1);

    for(int i = 0; i < int(accMoves.size()); ++i)
    {
        float value = float(winMoves[i]) / float(accMoves[i]);
        if(value > best)
        {
          best = value;
          best_index = i;
        }
    }

    coord.push_back(char(int('a') + possibleMoves[best_index*2]));
    coord.push_back(char(int('1') + possibleMoves[best_index*2+1]));
    return coord;
}