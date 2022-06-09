#pragma once

bool possibleMove(int** board, const int& x, const int& y, const int& player);
const std::vector<int> PossibleMoves(int** board, const int& player);
void Update(int** board, const int& x, const int& y, const int& player);

extern int directions[16];