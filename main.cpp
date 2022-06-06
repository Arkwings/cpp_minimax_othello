#include <iostream>
#include <string>
#include <filesystem>

#include "othello.hpp"

int argument_checks(const int& count, char ** arguments)
{
        bool wrong_arguments(false);
        if(count < 3) { std::cerr << "ERROR: not enough arguments to run the program" << std::endl; wrong_arguments = true; }
        if(count > 3) { std::cerr << "ERROR: too much arguments to run the program" << std::endl; wrong_arguments = true; }
        
        std::string p1(arguments[1]), p2(arguments[2]);
        if(p1 != "player" && !std::filesystem::exists(std::filesystem::path(p1))) { std::cerr << "ERROR: player 1 is not a player and IA binary can not be found" << std::endl; wrong_arguments = true; }
        if(p2 != "player" && !std::filesystem::exists(std::filesystem::path(p2))) { std::cerr << "ERROR: player 2 is not a player and IA binary can not be found" << std::endl; wrong_arguments = true; }

        if(wrong_arguments) { std::cerr << "command should be ./othello [IA1 binary | \"player\"] [IA2 binary | \"player\"] [optional:idle time]" << std::endl; return 1;}
        return 0;
}

int main(int argc, char * argv[])
{
        if(argument_checks(argc, &argv[0])) return 1;
        Othello(std::string(argv[1]), std::string(argv[2]), argc >= 3 ? int(argv[3][0] - '0'): 0);
        return 0;
}
