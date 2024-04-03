#pragma once
#include <SFML/Graphics.hpp>
#include "AssetManager.h"
#include <iostream>
#include <fstream>

class Table {
protected:
    sf::RectangleShape rectangle;
    int sizeText = 25;
public:
    Table();
    void setFormatRectangle(const sf::Color& OutlineColor);
    void setFormatText(sf::Text& text);
    virtual void setPositionTable(sf::RenderWindow& window) = 0;
    sf::RectangleShape& getRectangle();
};

class ResultsTable : public Table {
private:
    sf::Text result;
    sf::Text textRecord;
    int record;
public:
    ResultsTable();
    void setPositionTable(sf::RenderWindow& window);
    void setResult(int result);
    void setRecord(const std::string& pathRecordFile);
    void setNewRecord(const std::string& pathRecordFile, const int& NewRecord);
    sf::Text& getTextRecord();
    int& getRecord();
    sf::Text& getResult();
};

class FooterTable : public Table {
protected:
    sf::Text text;
public:
    FooterTable();
    void setPositionTable(sf::RenderWindow& window);
    void setText(std::string text);
    sf::Text& getText();
};

