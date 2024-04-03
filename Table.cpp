#include "Table.h"

void ResultsTable::setPositionTable(sf::RenderWindow& window) {
    rectangle.setPosition(0, 0);
    int width = window.getSize().x;
    int height = sizeText + 10;
    rectangle.setSize(sf::Vector2f(width, height));
}

ResultsTable::ResultsTable() {
    AssetManager::instance().setFont("font/conthrax-sb.ttf");
    setFormatText(result);
    setFormatText(textRecord);
    result.setPosition(5, 0);
    textRecord.setPosition(350, 0);
    setResult(0);
}

void Table::setFormatText(sf::Text& text) {
    text.setFillColor(sf::Color::Black);
    text.setFont(AssetManager::getFont());
    text.setCharacterSize(sizeText);
}

Table::Table() {
    setFormatRectangle(sf::Color(49, 49, 49));
}

void Table::setFormatRectangle(const sf::Color& OutlineColor) {
    rectangle.setFillColor(sf::Color::Transparent);
    rectangle.setOutlineColor(OutlineColor);
    rectangle.setOutlineThickness(2);
}

void ResultsTable::setResult(int result) {
    this->result.setString("step: " + std::to_string(result));
}

void ResultsTable::setRecord(const std::string& pathRecordFile) {
    std::ifstream recordFromFile;

    recordFromFile.open(pathRecordFile);

    if (recordFromFile.is_open()) {
        recordFromFile >> record;

        if (!record) {
            textRecord.setString("record: no result");
        }
        else {
            textRecord.setString("record: " + std::to_string(record));
        }

    }
    else {
        textRecord.setString("record: no result");
    }

    recordFromFile.close();
}

void ResultsTable::setNewRecord(const std::string& pathRecordFile, const int& NewRecord) {
    std::ofstream recordFromFile;
    recordFromFile.open(pathRecordFile);

    if (recordFromFile.is_open()) {
        recordFromFile << NewRecord;
    }

    recordFromFile.close();
}


sf::RectangleShape& Table::getRectangle() {
    return rectangle;
}

sf::Text& ResultsTable::getTextRecord() {
    return textRecord;
}

int& ResultsTable::getRecord() {
    return record;
}

sf::Text& ResultsTable::getResult() {
    return result;
}

FooterTable::FooterTable() {
    setFormatText(text);
    text.setPosition(5, 300);

}

void FooterTable::setPositionTable(sf::RenderWindow& window) {
    int width = window.getSize().x;
    int height = sizeText + 10;
    rectangle.setPosition(0, window.getSize().y - height);
    rectangle.setSize(sf::Vector2f(width, height));
}

void FooterTable::setText(std::string text) {
    this->text.setString(text);
    this->text.setPosition(5, rectangle.getPosition().y);
}

sf::Text& FooterTable::getText() {
    return text;
}
