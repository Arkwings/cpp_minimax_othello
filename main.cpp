#include <iostream>
#include <string>
#include <filesystem>
#include <vector>

#include "color.hpp"
#include "othello.hpp"

int argument_checks(const int& count, char ** arguments)
{
        bool wrong_arguments(false);
        if(count < 3) 
	{ 
		std::cerr << error_col.start() << "ERROR: not enough arguments to run the program" << error_col.end() << std::endl; 
		wrong_arguments = true; 
	}
	else if(count > 4) 
	{ 
		std::cerr << error_col.start() << "ERROR: too much arguments to run the program" << error_col.end() << std::endl; 
		wrong_arguments = true; 
	}
	else
	{
        	std::string p1(arguments[1]), p2(arguments[2]);
        	if(p1 != "player" && !std::filesystem::exists(std::filesystem::path(p1))) 
		{ 
			std::cerr << error_col.start() << "ERROR: player 1 is not a player and IA binary can not be found" << error_col.end() << std::endl; 
			wrong_arguments = true; 
		}
        	if(p2 != "player" && !std::filesystem::exists(std::filesystem::path(p2))) 
		{ 
			std::cerr << error_col.start() << "ERROR: player 2 is not a player and IA binary can not be found" << error_col.end() << std::endl; 
			wrong_arguments = true; 
		}
		if(count == 4)
		{
			try
			{
				std::stoi(std::string(arguments[3]));
			}
			catch(...)
			{
				std::cerr << error_col.start() << "ERROR: idle time specified couldn't be converted to INT" << error_col.end() << std::endl;
				wrong_arguments = true;
			}
		}
	}

        if(wrong_arguments) 
	{ 
		std::cerr << error_col.start() <<  "command should be ./othello [IA1 binary | \"player\"] [IA2 binary | \"player\"] [optional:idle time]" << error_col.end() << std::endl; 
		return 1;
	}
        return 0;
}

int main(int argc, char * argv[])
{
        if(argument_checks(argc, &argv[0])) return 1;
        Othello(std::string(argv[1]), std::string(argv[2]), argc >= 3 ? int(argv[3][0] - '0'): 0);
        return 0;
}
