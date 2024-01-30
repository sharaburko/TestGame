#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

namespace userColor {
	sf::Color Fuchsia(255, 0, 255);
	sf::Color Teal(0, 128, 128);
	sf::Color Purple(128, 0, 12);
	sf::Color Gray(128, 128, 128);
	sf::Color Navy(0, 0, 128);
	sf::Color Lime(0, 255, 0);
	sf::Color Aqua(0, 255, 255);
	sf::Color Olive(128, 128, 0);
}

std::vector <sf::Color> arrColor{ sf::Color::Black, sf::Color::White, sf::Color::Green, sf::Color::Blue, sf::Color::Magenta, userColor::Purple, userColor::Olive, userColor::Gray, userColor::Navy, userColor::Fuchsia, userColor::Teal };    //color points and chip
