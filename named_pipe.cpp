#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <cstring>

#include <iostream>
#include <string>
#include <vector>

#include "color.hpp"
#include "named_pipe.hpp"
#include "othello.hpp"

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

    for(std::string::const_iterator str_it = text.begin(); str_it != text.end();)
    {   
        int array_it = 0;
        while(array_it < TEXT_ARRAY_LENGTH)
        {
            text_array_[array_it] = *str_it;
            ++str_it;
            ++array_it;

            if(str_it == text.end())    break;
        }
        write(fd, text_array_, array_it);
    }
    close(fd);
}

void Pipe::Read(std::string& text)
{
    int fd = open(filepath_.c_str(), O_RDONLY);
    text.clear();
    for(int it=0; it < TEXT_ARRAY_LENGTH; ++it) text_array_[it] = '\0';

    read(fd, text_array_, 2);
    text.append(text_array_);

    close(fd);
}
