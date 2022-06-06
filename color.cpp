#include <string>

#include "color.hpp"

Color error_col("231", "196");

const std::string Color::start()
{
	return std::string(COLOR_START) + TEXT_START + text_color_ + ";" + BACK_START + back_color_ + "m ";
}

const std::string Color::end()
{
	return std::string(COLOR_END);
}
