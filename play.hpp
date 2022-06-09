#pragma once

class Human
{
public:
	static std::tuple<int, int> Play();
};

class IA
{
public:
	static std::tuple<int, int> Play(const int& player, int** board, const int& idle_time);
private:
	static Pipe* IA_com_;
};
