#include "menu.h"

Menu::Menu(const std::string& Title, unsigned modeWidth, unsigned modeHeight) {
	window.create(sf::VideoMode(modeWidth, modeHeight), Title, sf::Style::Close);
}

Menu::Menu() {
	window.create(sf::VideoMode(640, 480), "Sharaburko_Game", sf::Style::Close);
}

Menu::Menu(const std::string& Title) {
	window.create(sf::VideoMode(640, 480), Title, sf::Style::Close);
}

int Menu::run() {

	 while (window.isOpen()) {
		 insert();
		 update();
		 draw();

		 if (mouse.isButtonPressed(sf::Mouse::Left) && activItem > 0) {
			 window.close();
			 return activItem;
		 }

	 }
}

void Menu::setMenuItem(){
	AssetManager::instance().setFont("font/conthrax-sb.ttf");

	menuItem.reserve(countMenuItem);

	menuItem.emplace_back("Level 1", AssetManager::instance().getFont());
	menuItem.emplace_back("Level 2", AssetManager::instance().getFont());
	menuItem.emplace_back("EXIT", AssetManager::instance().getFont());

	//float positionX = 250;
	float positionY = 50;

	for (auto &item : menuItem) {
		item.setCharacterSize(50);

		float positionX = positionTextX(item.getGlobalBounds().getSize());

		item.setPosition(positionX, positionY);
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
	}
	activItem = 0;

	menuItem.clear();

	setMenuItem();

	mousePosition = mouse.getPosition(window);
}

void Menu::update() {

	for (int position = 0; auto & item : menuItem) {
		position++;

		if (sf::IntRect(item.getGlobalBounds()).contains(mousePosition)) {
			getSoundSelectItemMenu().play();
			item.setFillColor(sf::Color::Red);
			activItem = position;
			item.move(3, 3);
		}

	}

}

void Menu::draw() {
	window.clear(sf::Color(sf::Color::Black));
	window.draw(AssetManager::instance().getBackground("img/back_menu.jpg"));

	for (auto & item : menuItem) {
		window.draw(item);
	}

	window.display();
}
float Menu::positionTextX(sf::Vector2f sizeText) {
	return ( window.getSize().x / 2  - sizeText.x / 2);
}


sf::Sound& Menu::getSoundSelectItemMenu() {
	auto &manager = AssetManager::instance();
	manager.setBuffer("music/click.mp3");
	soundSelectItemMenu.setBuffer(manager.getBuffer());

	return soundSelectItemMenu;
}