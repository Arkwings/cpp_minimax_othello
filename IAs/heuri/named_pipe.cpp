#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <cstring>

#include <string>

#include "heuristic.hpp"
#include "named_pipe.hpp"

Pipe::Pipe(const std::string& filepath, const int& permission)
: filepath_(filepath)
, permission_(permission)
{
    mkfifo(filepath_.c_str(), permission_);
}

void Pipe::Write(const std::string& text)
{
    int fd = open(filepath_.c_str(), O_WRONLY);
    for(int it=0; it < TEXT_ARRAY_LENGTH; ++it) text_array_[it] = '\0';

    //coords
    text_array_[0] = text[0];
    text_array_[1] = text[1];

    write(fd, text_array_, 2);

    close(fd);
}

void Pipe::Read(std::string& text)
{
    int fd = open(filepath_.c_str(), O_RDONLY);
    text.clear();
    for(int it=0; it < TEXT_ARRAY_LENGTH; ++it) text_array_[it] = '\0';

    int reste = BOARD_SIZE * BOARD_SIZE + 1;
    for(int fifo_it = 0; fifo_it < BOARD_SIZE * BOARD_SIZE + 1; fifo_it += TEXT_ARRAY_LENGTH) //read as much as needed if board bigger than text array size
    {
        read(fd, text_array_, reste > TEXT_ARRAY_LENGTH ? TEXT_ARRAY_LENGTH: reste);
        text.append(text_array_);
        reste-=TEXT_ARRAY_LENGTH;
    }

    close(fd);
}
