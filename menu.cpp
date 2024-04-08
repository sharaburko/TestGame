#include "menu.h"

int Menu::run(sf::RenderWindow& window, sf::Mouse& mouse) {

	 while (window.isOpen()) {
		 insert();
		 update(window, mouse);
	  	 draw(window);

		 if (mouse.isButtonPressed(sf::Mouse::Left) && activItem > 0) {
			 window.clear();
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
	activItem = 0;
	menuItem.clear();
	setMenuItem();
}

void Menu::update(sf::RenderWindow& window, sf::Mouse& mouse) {

	for (int position = 0; auto & item : menuItem) {
		position++;

		if (sf::IntRect(item.getLocalBounds()).contains(mouse.getPosition(window))) {
			getSoundSelectItemMenu().play();
			item.setFillColor(sf::Color::Red);
			activItem = position;
			item.move(3, 3);
		}

	}

}

void Menu::draw(sf::RenderWindow& window) {
	window.clear(sf::Color(sf::Color::Black));
	window.draw(AssetManager::instance().getBackground("img/back_menu.jpg"));

	for (auto & item : menuItem) {
		window.draw(item);
	}

	window.display();
}
float Menu::positionTextX(sf::Vector2f sizeText, sf::RenderWindow& window) {
	return ( window.getSize().x / 2  - sizeText.x / 2);
}

const int& Menu::getActivItem()
{
	return activItem;
}


sf::Sound& Menu::getSoundSelectItemMenu() {
	auto &manager = AssetManager::instance();
	manager.setBuffer("music/click.mp3");
	soundSelectItemMenu.setBuffer(manager.getBuffer());

	return soundSelectItemMenu;
}