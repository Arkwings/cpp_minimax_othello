#include <cstdlib>
#include <ctime>
#include <cstring>

#include <string>
#include <vector>
#include <iostream>
#include <random>

#include "othello.hpp"
#include "montecarlo.hpp"

//declaring everything here to reduce mem alloc time
std::random_device rd;
std::mt19937 rng(rd());
std::vector<int> moves;
std::vector<int> moves2;
int** new_board;
int x, y, x2, y2, dir_it, move, move2, color_copy, points, iterations;
bool end, passed, possible, oponent_found, propagate;

//all in one ugly func to simulate quicker
bool playRandomGame(const int& color)
{
    move2 = -1; color_copy = color; points = 0;
	end = false; passed = false;
    
	while(!end)
	{	
		moves2.clear();

	    for(y = 0; y < BOARD_SIZE; ++y)
	    {
		    for(x = 0; x < BOARD_SIZE; ++x)
		    {
                possible = false;
                if(new_board[x][y] == 0)
                {
	                for(dir_it = 0; dir_it < int(sizeof(directions) / sizeof(int)) && !possible; dir_it+=2)
	                {
		                oponent_found = false;
		                for(x2 = x + directions[dir_it], y2 = y + directions[dir_it + 1]
                        ; x2 > -1 && y2 > -1 && x2 < BOARD_SIZE && y2 < BOARD_SIZE
                        ; x2 += directions[dir_it], y2 += directions[dir_it + 1])
		                {
			                if(new_board[x2][y2] == 0 || (new_board[x2][y2] == color_copy && oponent_found == false)) break;
			                else if(new_board[x2][y2] == color_copy * -1) oponent_found = true;
			                else 
                            {
                                possible = true;
                                break;
                            }
		                }
	                }
                }

			    if(possible)
			    {
				    moves2.push_back(x);
				    moves2.push_back(y);
			    }
		    }
	    }

        std::uniform_int_distribution<int> gen(0, moves2.size()/2 - 1); // uniform, unbiased
		
		if(!moves2.empty())
		{
			passed = false;
			move2 = gen(rng);
            
            //update the board
            x = moves2[move2*2];
            y = moves2[move2*2 + 1];
            new_board[x][y] = color_copy;

	        for(dir_it = 0; dir_it < int(sizeof(directions) / sizeof(int)); dir_it+=2)
	        {
		        propagate = false;
		        oponent_found = false;
		        for(x2 = x + directions[dir_it], y2 = y + directions[dir_it + 1]
                ; x2 > -1 && y2 > -1 && x2 < BOARD_SIZE && y2 < BOARD_SIZE
                ; x2 += directions[dir_it], y2 += directions[dir_it + 1])
		        {
		    	    if(new_board[x2][y2] == 0 || (new_board[x2][y2] == color_copy && oponent_found == false)) break;
		    	    else if(new_board[x2][y2] == color_copy * -1) oponent_found = true;
		    	    else propagate = true;
		        }
		        if(propagate)
		        {
		    	    for(x2 = x + directions[dir_it], y2 = y + directions[dir_it + 1]
                    ; x2 > -1 && y2 > -1 && x2 < BOARD_SIZE && y2 < BOARD_SIZE
                    ; x2 += directions[dir_it], y2 += directions[dir_it + 1])	
		    	    {
		    		    if(new_board[x2][y2] == color_copy * -1)	new_board[x2][y2] = color_copy;
		    		    else break;
		    	    }
		        }
	        }
		}
		else
		{
			if(passed) end = true;
			passed = true;
		}
		
		color_copy = -color_copy;
	}

	for(y = 0; y < BOARD_SIZE; ++y)
	{
		for(x = 0; x < BOARD_SIZE; ++x)
			points += new_board[x][y];
	}

    if((color == 1 && points > 0) || (color == -1 && points < 0))    return true;
    return false;
}

const std::string montecarlo(int** board, const int& color, const int& IA_time)
{
    moves = PossibleMoves(board, color);
    std::vector<int> accMoves(moves.size()/2);
    std::vector<int> winMoves(moves.size()/2);
    for(x = 0; x < int(accMoves.size()); ++x)    accMoves[x] = 0;
    for(x = 0; x < int(winMoves.size()); ++x)    winMoves[x] = 0;

    std::uniform_int_distribution<int> gen(0, moves.size()/2 - 1); // uniform, unbiased

    iterations = 0; move = -1;
    std::string coord("");

    time_t start_time(time(NULL));
    time_t moving_time(start_time);
    time_t end_time(start_time + time_t(IA_time));
    time_t iteration_time(end_time);

    std::cout << "montecarlo start time: " << ctime(&start_time) << std::endl;

    do
    {
        // for(y = 0; y < BOARD_SIZE; ++y)                                      //reset array
        // {
        //     for(x = 0; x < BOARD_SIZE; ++x)
        //         new_board[x][y] = board[x][y];
        // }  
        for(y = 0; y < BOARD_SIZE; ++y)                                         //reset array, best ?
            memcpy(new_board[y], board[y], BOARD_SIZE*sizeof(int));

        move = gen(rng);                                                        //pick move
        Update(new_board, moves[move*2], moves[move*2+1], color);               //update the board
        ++accMoves[move];                                                       //update this move counter
        if(!playRandomGame(-color))    ++winMoves[move];                        //do a random game and update win counter

        moving_time = time(NULL);
        if(++iterations == 1)   iteration_time = moving_time - start_time;
    } while (moving_time < end_time - 3 * iteration_time); //we remove 3 iteration times to have the time to quit the program

    std::cout << "montecarlo end time: " << ctime(&end_time) << std::endl;

    float best(-1);
    int best_index(-1);

    for(x = 0; x < int(accMoves.size()); ++x)
    {
        float value = float(winMoves[x]) / float(accMoves[x]);
        if(value > best)
        {
          best = value;
          best_index = x;
        }
    }

    for(x = 0; x < int(accMoves.size()); ++x)   std::cout << winMoves[x] << " / " << accMoves[x] << std::endl;

    coord.push_back(char(int('a') + moves[best_index*2]));
    coord.push_back(char(int('1') + moves[best_index*2+1]));
    return coord;
}