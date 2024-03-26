#include "menu.h"

Menu::Menu(const std::string& Title, unsigned modeWidth, unsigned modeHeight) {
	window.create(sf::VideoMode(modeWidth, modeHeight), Title, sf::Style::Close);
}

Menu::Menu() {
	window.create(sf::VideoMode(640, 480), "Sharaburko_Game", sf::Style::Close);
}

void Menu::run() {
	 setMenuItem();

	 while (window.isOpen()) {
		 insert();
		 update();
		 draw();

		 if (mouse.isButtonPressed(sf::Mouse::Left)) {
			 switch (activItem) {
			 case 3: window.close();
			 }

		 }
	 }
}

void Menu::setMenuItem(){
	menuItem.reserve(countMenuItem);
	AssetManager::instance().setFont("font/conthrax-sb.ttf");

	menuItem.emplace_back("Level 1", AssetManager::instance().getFont());
	menuItem.emplace_back("Level 2", AssetManager::instance().getFont());
	menuItem.emplace_back("EXIT", AssetManager::instance().getFont());

	float positionX = 250;
	float positionY = 50;

	for (auto &item : menuItem) {
		item.setPosition(positionX, positionY);
		item.setCharacterSize(50);
		item.setFillColor(sf::Color::Black);
		item.setOutlineThickness(2);
		item.setOutlineColor(sf::Color::White);
		positionY += 70;
	}
}

void Menu::insert() {

	while (window.pollEvent(event)) {

		if (event.type == sf::Event::Closed)
			window.close();

		if (event.type == sf::Keyboard::Escape)
			window.close();
	}

	mousePosition = mouse.getPosition(window);
}

void Menu::update() {

	for (int position = 0; auto & item : menuItem) {
		position++;

		if (sf::IntRect(item.getGlobalBounds()).contains(mousePosition)) {
			item.setFillColor(sf::Color::Red);
			activItem = position;
		}
		else {
			item.setFillColor(sf::Color::Black);
			activItem = 0;
		}

	}

	std::cout << activItem << "\n";
}

void Menu::draw() {
	window.clear(sf::Color(sf::Color::Black));
	window.draw(AssetManager::instance().getBackground("img/back_menu.jpg"));

	for (auto & item : menuItem) {
		window.draw(item);
	}

	window.display();
}

