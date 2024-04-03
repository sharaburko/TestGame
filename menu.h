#pragma once
#include "AssetManager.h"
#include <vector>

class Menu {
private:
	sf::RenderWindow window;
	sf::Event event;
	sf::Mouse mouse;
	sf::Vector2i mousePosition;
	int activItem = 0;
	sf::Sound soundSelectItemMenu;

	std::vector <sf::Text> menuItem;
	size_t countMenuItem = 3;

	void setMenuItem();
	void insert();
	void update();
	void draw();
	float positionTextX(sf::Vector2f sizeText);
	sf::Sound& getSoundSelectItemMenu();
	
public:
	Menu(const std::string& Title, unsigned modeWidth, unsigned modeHeight);
	Menu(const std::string& Title);
	Menu();
	int run();
};