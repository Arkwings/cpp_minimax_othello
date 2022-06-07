#pragma once

class Human
{
public:
	static std::tuple<int, int> Play(const std::vector<int>& moves, const int& player, int** board);
};

class IA
{
public:
	static std::tuple<int, int> Play(const std::vector<int>& moves, const int& player, int** board);
};
