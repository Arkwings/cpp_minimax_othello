#include <vector>
#include <limits>
#include <string>

#include "othello.hpp"
#include "heuristic.hpp"

#define PARITY_WEIGHT 10
#define FRONT_PARITY_WEIGHT 75
#define MOBILITY_WEIGHT 75
#define CORNER_WEIGHT 600
#define CORNER_CLOSENESS_WEIGHT 300
#define BORDER_WEIGHT 150

int parity(int** board, const int& color)
{
    int player(0), opponent(0);

    for(int y = 0; y < BOARD_SIZE; ++y)
    {
        for(int x = 0; x < BOARD_SIZE; ++x)
        {
            if(board[x][y] == 0)            continue;
            else if(board[x][y] == color)   ++player;
            else                            ++opponent;
        }
    }

    if(player == 0 && opponent == 0)return 0;
    else if(player > opponent)       return (100 * player) / (player + opponent);
    else if(opponent > player)  return -(100 * opponent) / (player + opponent);
    return 0;
}

int front_parity(int** board, const int& color)
{
    int player(0), opponent(0);

    for(int y = 0; y < BOARD_SIZE; ++y)
    {
        for(int x = 0; x < BOARD_SIZE; ++x)
        {
            if(board[x][y] == color)
            {
                for(int dir = 0; dir < int(sizeof(directions) / sizeof(int)); dir += 2)
                {
                    if(x + directions[dir] >= 0 && x + directions[dir] < BOARD_SIZE && y + directions[dir + 1] >= 0 && y + directions[dir + 1] < BOARD_SIZE)
                    {
                        if(board[x + directions[dir]][y + directions[dir + 1]] == 0)   ++player;
                    }
                }
            }
            if(board[x][y] == -color)
            {
                for(int dir = 0; dir < int(sizeof(directions) / sizeof(int)); dir += 2)
                {
                    if(x + directions[dir] >= 0 && x + directions[dir] < BOARD_SIZE && y + directions[dir + 1] >= 0 && y + directions[dir + 1] < BOARD_SIZE)
                    {
                        if(board[x + directions[dir]][y + directions[dir + 1]] == 0)   ++opponent;
                    }
                }
            }
        }
    }

    if(player == 0 && opponent == 0)return 0;
    else if(player > opponent)  return -(100 * player) / (player + opponent);
    else if(opponent > player)  return (100 * opponent) / (player + opponent);
    return 0;
}

int mobility(int** board, const int& color)
{
    int player(PossibleMoves(board, color).size() / 2), opponent(PossibleMoves(board, -color).size() / 2);
    
    if(player == 0 && opponent == 0)return 0;
    else if(player > opponent)      return (100 * player) / (player + opponent);
    else if(opponent > player)      return -(100 * opponent) / (player + opponent);
    return 0;
}

int corners(int** board, const int& color)
{
    int player(0), opponent(0);

    if(board[0][0] == color)            ++player;
    else if(board[0][0] == -color)      ++opponent;

    if(board[BOARD_SIZE - 1][0] == color)            ++player;
    else if(board[BOARD_SIZE - 1][0] == -color)      ++opponent;

    if(board[0][BOARD_SIZE - 1] == color)            ++player;
    else if(board[0][BOARD_SIZE - 1] == -color)      ++opponent;

    if(board[BOARD_SIZE - 1][BOARD_SIZE - 1] == color)            ++player;
    else if(board[BOARD_SIZE - 1][BOARD_SIZE - 1] == -color)      ++opponent;

    return 25 * (player - opponent);
}

int corner_closeness(int** board, const int& color)
{
    int player(0), opponent(0);

    if(board[0][1] == color)            ++player;
    else if(board[0][1] == -color)      ++opponent;
    if(board[1][1] == color)            ++player;
    else if(board[1][1] == -color)      ++opponent;
    if(board[1][0] == color)            ++player;
    else if(board[1][0] == -color)      ++opponent;

    if(board[BOARD_SIZE - 1][1] == color)            ++player;
    else if(board[BOARD_SIZE - 1][1] == -color)      ++opponent;
    if(board[BOARD_SIZE - 2][1] == color)            ++player;
    else if(board[BOARD_SIZE - 2][1] == -color)      ++opponent;
    if(board[BOARD_SIZE - 2][0] == color)            ++player;
    else if(board[BOARD_SIZE - 2][0] == -color)      ++opponent;

    if(board[1][BOARD_SIZE - 1] == color)            ++player;
    else if(board[1][BOARD_SIZE - 1] == -color)      ++opponent;
    if(board[1][BOARD_SIZE - 2] == color)            ++player;
    else if(board[1][BOARD_SIZE - 2] == -color)      ++opponent;
    if(board[0][BOARD_SIZE - 2] == color)            ++player;
    else if(board[0][BOARD_SIZE - 2] == -color)      ++opponent;

    if(board[BOARD_SIZE - 2][BOARD_SIZE - 1] == color)            ++player;
    else if(board[BOARD_SIZE - 2][BOARD_SIZE - 1] == -color)      ++opponent;
    if(board[BOARD_SIZE - 2][BOARD_SIZE - 2] == color)            ++player;
    else if(board[BOARD_SIZE - 2][BOARD_SIZE - 2] == -color)      ++opponent;
    if(board[BOARD_SIZE - 1][BOARD_SIZE - 2] == color)            ++player;
    else if(board[BOARD_SIZE - 1][BOARD_SIZE - 2] == -color)      ++opponent;

    return -12.5 * (player - opponent);
}

int borders(int** board, const int& color)
{
    int player(0), opponent(0);

    for(int it = 1; it < BOARD_SIZE - 1; ++it)
    {
        if(board[it][0] == color)                           ++player;
        else if(board[it][0] == -color)                     ++opponent;

        if(board[it][BOARD_SIZE - 1] == color)              ++player;
        else if(board[it][BOARD_SIZE - 1] == -color)        ++opponent;

        if(board[0][it] == color)                           ++player;
        else if(board[0][it] == -color)                     ++opponent;

        if(board[BOARD_SIZE - 1][it] == color)              ++player;
        else if(board[BOARD_SIZE - 1][it] == -color)        ++opponent;
    }

    return 12.5 * (player - opponent);
}

int heuristic(int** board, const int& color)
{
    return PARITY_WEIGHT * parity(board, color) + FRONT_PARITY_WEIGHT * front_parity(board, color) + MOBILITY_WEIGHT * mobility(board, color) + CORNER_WEIGHT * corners(board, color) + CORNER_CLOSENESS_WEIGHT * corner_closeness(board, color) + BORDER_WEIGHT * borders(board, color);
}

const std::string heuristics(int** board, const int& color)
{
    int x_save(-1), y_save(-1), value_save(std::numeric_limits<int>::min());
    std::vector<int> moves = PossibleMoves(board, color);
    std::string coord("");

	int** board_copy = new int*[BOARD_SIZE];
	for(int i = 0; i < BOARD_SIZE; ++i) board_copy[i] = new int[BOARD_SIZE];

    for(int z = 0; z < int(moves.size()); z+=2)
    {
        //reset
        for(int y = 0; y < BOARD_SIZE; ++y)
        {
            for(int x = 0; x < BOARD_SIZE; ++x)
            {
                board_copy[x][y] = board[x][y];
            }
        }
        //update
        Update(board_copy, moves[z], moves[z+1], color);
        
        //get heuri
        int heuri = heuristic(board_copy, color);
        if(heuri > value_save)
        {
            x_save = moves[z];
            y_save = moves[z+1];
            value_save = heuri;
        }
    }

    for(int i = 0; i < BOARD_SIZE; ++i) delete board_copy[i];
	delete board_copy;

    coord.push_back(char(int('a') + x_save));
    coord.push_back(char(int('1') + y_save));
    return coord;
}