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
    pathRecordFile = ".r";
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

void ResultsTable::setRecord(const int &level) {
    std::fstream recordFromFile;

    recordFromFile.open(pathRecordFile, std::ios::in | std::ios::out);

    if (recordFromFile.is_open()) {
        constexpr int level_offset = 1;
        recordFromFile.seekg((level - level_offset) * sizeof(int));
        recordFromFile.read((char*)&record, sizeof(int));
        recordFromFile.seekg(0, std::ios::beg);

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

void ResultsTable::setNewRecord(const int &level, const int& NewRecord) {
    std::ofstream recordFromFile;
    recordFromFile.open(pathRecordFile);
    constexpr int level_offset = 1;

    if (recordFromFile.is_open()) {
        recordFromFile.seekp((level - level_offset) * sizeof(int));
        recordFromFile.write((char*)&NewRecord, sizeof(int));
        recordFromFile.seekp(0, std::ios::beg);    
    }
    else {
        std::cout << "Error. Not file record\n";
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
