#pragma once
#include <SFML/Graphics.hpp>
#include "AssetManager.h"
#include <vector>
#include <iostream>

class Menu {
private:
	sf::RenderWindow window;
	sf::Event event;
	sf::Mouse mouse;
	sf::Vector2i mousePosition;
	int activItem = 0;

	std::vector <sf::Text> menuItem;
	size_t countMenuItem = 3;

	void setMenuItem();
	void insert();
	void update();
	void draw();
	
public:
	Menu(const std::string& Title, unsigned modeWidth, unsigned modeHeight);
	Menu();
	void run();

};