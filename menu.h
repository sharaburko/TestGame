#pragma once
#include "AssetManager.h"
#include <vector>
#include <iostream>

class Menu {
private:
	int activItem = 0;
	sf::Sound soundSelectItemMenu;

	std::vector <sf::Text> menuItem;
	size_t countMenuItem = 3;

	void setMenuItem(sf::RenderWindow& window);

	float positionTextX(sf::Vector2f sizeText, sf::RenderWindow& window);
	const int &getActivItem();
	sf::Sound& getSoundSelectItemMenu();

	void insert(sf::RenderWindow& window);
	void update(sf::RenderWindow& window, sf::Mouse& mouse);
	void draw(sf::RenderWindow& window);
	void initializingMenu(sf::RenderWindow& window);
	
public:
	int run(sf::RenderWindow& window, sf::Mouse& mouse);
};