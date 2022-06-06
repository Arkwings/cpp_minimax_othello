#pragma once

#define COLOR_START "\033["
#define TEXT_START "38;5;"
#define BACK_START "48;5;"
#define COLOR_END "\033[m"

class Color
{
public:
	Color(const std::string& text_color, const std::string& back_color)
	: text_color_(text_color)
	, back_color_(back_color)
	{}

	~Color()
	{}

	const std::string start();
	const std::string end();
private:
	const std::string text_color_;
	const std::string back_color_;
};

extern Color error_col;
