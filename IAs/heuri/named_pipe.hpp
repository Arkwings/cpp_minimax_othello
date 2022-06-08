#pragma once

#define TEXT_ARRAY_LENGTH 80

class Pipe
{
public:
    Pipe(const std::string& filepath, const int& permission);
    ~Pipe() {}

    void Write(const std::string& text);
    void Read(std::string& text);

private:
    const std::string filepath_;
    const int permission_;
    
    char text_array_[TEXT_ARRAY_LENGTH];
};