#include <iostream>
#include <vector>
#include <tuple>

#include "color.hpp"
#include "play.hpp"

std::tuple<int, int> Human::Play(const std::vector<int>& moves, const int& player, int** board)
{
	return std::tuple<int, int>(0, 0);
}

std::tuple<int, int> IA::Play(const std::vector<int>& moves, const int& player, int** board)
{
	return std::tuple<int, int>(0, 0);
}

