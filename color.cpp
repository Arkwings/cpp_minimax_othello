#include <string>

#include "color.hpp"

const Color error_col("231", "196");

const std::string Color::start() const
{
	return std::string(COLOR_START) + TEXT_START + text_color_ + ";" + BACK_START + back_color_ + "m";
}

const std::string Color::end() const
{
	return std::string(COLOR_END);
}
